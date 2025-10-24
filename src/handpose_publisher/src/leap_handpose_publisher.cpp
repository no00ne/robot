// src/leap_handpose_publisher.cpp
// ROS2 rclcpp node: read LeapC, map Leap -> arm frame, publish absolute position (m)
// and desired flange orientation as ZYX Euler RX/RY/RZ (millideg), plus hand_id,
// tracking frame_id, pinch_strength, header.stamp and header.frame_id.
// NO smoothing / NO limits / NO relative position / NO IK -- raw low-latency publisher.

#include <rclcpp/rclcpp.hpp>
#include "handpose_interfaces/msg/hand_flange.hpp"
#include <cmath>
#include <chrono>
#include <stdexcept>
#include "LeapC.h"

using namespace std::chrono_literals;

/* ensure M_PI */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

static constexpr double ANGLE_DEG = 45.0;
static constexpr double RAD2DEG = 180.0 / M_PI;
static constexpr double MILLIDEG = 1000.0;

/* ---------- axis map: arm = ( -Z_leap, -X_leap, Y_leap ) ; mm -> m ---------- */
static inline void map_mm_to_m(const LEAP_VECTOR *L, double out_arm[3]) {
  out_arm[0] = -(double)L->z * 0.001;  /* X_arm = -Z_leap (m) */
  out_arm[1] = -(double)L->x * 0.001;  /* Y_arm = -X_leap (m) */
  out_arm[2] =  (double)L->y * 0.001;  /* Z_arm =  Y_leap (m) */
}

/* direction mapping: same axes but no scaling */
static inline void map_dir_leap_to_arm(const LEAP_VECTOR *L, double out_arm[3]) {
  out_arm[0] = -(double)L->z;
  out_arm[1] = -(double)L->x;
  out_arm[2] =  (double)L->y;
}

/* basic vector helpers */
static inline double vnorm(const double a[3]) {
  return std::sqrt(a[0]*a[0] + a[1]*a[1] + a[2]*a[2]);
}
static inline void vcopy(const double a[3], double b[3]) { b[0]=a[0]; b[1]=a[1]; b[2]=a[2]; }
static inline void vsub(const double a[3], const double b[3], double out[3]) {
  out[0]=a[0]-b[0]; out[1]=a[1]-b[1]; out[2]=a[2]-b[2];
}
static inline double vdot(const double a[3], const double b[3]) { return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]; }
static inline void vcross(const double a[3], const double b[3], double out[3]) {
  out[0] = a[1]*b[2] - a[2]*b[1];
  out[1] = a[2]*b[0] - a[0]*b[2];
  out[2] = a[0]*b[1] - a[1]*b[0];
}
static inline bool vnormalize(double a[3]) {
  double n = vnorm(a); if (n < 1e-12) return false; a[0]/=n; a[1]/=n; a[2]/=n; return true;
}

/* Rodrigues rotate: rotate vec about unit axis by angle (rad) */
static inline void rodrigues_rotate(const double vec[3], const double axis[3], double angle, double out[3]) {
  double c = cos(angle), s = sin(angle);
  double kdotv = vdot(axis, vec);
  double crossv[3]; vcross(axis, vec, crossv);
  out[0] = vec[0]*c + crossv[0]*s + axis[0]*kdotv*(1.0-c);
  out[1] = vec[1]*c + crossv[1]*s + axis[1]*kdotv*(1.0-c);
  out[2] = vec[2]*c + crossv[2]*s + axis[2]*kdotv*(1.0-c);
}

/* build rotation matrix from axis (X) and chosen approach vector (Z).
   Columns are X, Y, Z (so R[:,0]=X, R[:,1]=Y, R[:,2]=Z) */
static inline void build_rotation_from_axis_chosen(const double axis[3], const double chosen[3], double R[3][3]) {
  double X[3], Y[3], Z[3];
  vcopy(axis, X); vnormalize(X);
  vcopy(chosen, Z); vnormalize(Z);
  vcross(Z, X, Y); vnormalize(Y);
  double tmpX[3]; vcross(Y, Z, tmpX); vnormalize(tmpX); vcopy(tmpX, X);
  R[0][0] = X[0]; R[0][1] = Y[0]; R[0][2] = Z[0];
  R[1][0] = X[1]; R[1][1] = Y[1]; R[1][2] = Z[1];
  R[2][0] = X[2]; R[2][1] = Y[2]; R[2][2] = Z[2];
}

/* rotation matrix -> ZYX (rx around X, ry around Y, rz around Z) */
static inline void rotmat_to_euler_zyx(const double R[3][3], double &rx, double &ry, double &rz) {
  double r11=R[0][0], r12=R[0][1], r13=R[0][2];
  double r21=R[1][0], r22=R[1][1], r23=R[1][2];
  double r31=R[2][0], r32=R[2][1], r33=R[2][2];

  double sy = -r31;
  if (sy <= -1.0) ry = -M_PI_2;
  else if (sy >= 1.0) ry = M_PI_2;
  else ry = asin(sy);
  rx = atan2(r32, r33);
  rz = atan2(r21, r11);
}

/* Leap connection handle */
static LEAP_CONNECTION g_conn = NULL;

class LeapPublisherNode : public rclcpp::Node {
public:
  LeapPublisherNode()
  : Node("leap_handpose_publisher") {
    // parameter: header.frame_id for published Pose (world/base frame name)
    this->declare_parameter<std::string>("frame_id", "piper_base");
    frame_id_ = this->get_parameter("frame_id").as_string();

    pub_ = this->create_publisher<handpose_interfaces::msg::HandFlange>("handpose/flange", 10);

    // init LeapC
    eLeapRS rs = LeapCreateConnection(NULL, &g_conn);
    if (rs != eLeapRS_Success) {
      RCLCPP_ERROR(this->get_logger(), "LeapCreateConnection failed: %d", rs);
      throw std::runtime_error("LeapCreateConnection failed");
    }
    rs = LeapOpenConnection(g_conn);
    if (rs != eLeapRS_Success) {
      LeapCloseConnection(g_conn); g_conn = NULL;
      RCLCPP_ERROR(this->get_logger(), "LeapOpenConnection failed: %d", rs);
      throw std::runtime_error("LeapOpenConnection failed");
    }

    timer_ = this->create_wall_timer(10ms, std::bind(&LeapPublisherNode::loop, this));
    RCLCPP_INFO(this->get_logger(), "leap_handpose_publisher started (frame_id=%s)", frame_id_.c_str());
  }

  ~LeapPublisherNode() {
    if (g_conn) { LeapCloseConnection(g_conn); g_conn = NULL; }
  }

private:
  void loop() {
    if (!g_conn) return;
    LEAP_CONNECTION_MESSAGE msg;
    eLeapRS rs = LeapPollConnection(g_conn, 0, &msg);
    if (rs == eLeapRS_Timeout) return;
    if (rs != eLeapRS_Success) {
      RCLCPP_WARN(this->get_logger(), "LeapPollConnection failed: %d", rs);
      return;
    }

    if (msg.type != eLeapEventType_Tracking || !msg.tracking_event) return;
    const LEAP_TRACKING_EVENT *te = msg.tracking_event;
    if (te->nHands == 0) {
      // no hands -> do not publish
      return;
    }

    // choose nearest hand by palm position (Leap mm)
    int best = -1; double best_d2 = 1e300;
    for (uint32_t i=0;i<te->nHands;i++){
      const LEAP_HAND *h = &te->pHands[i];
      double dx = h->palm.position.x, dy = h->palm.position.y, dz = h->palm.position.z;
      double d2 = dx*dx + dy*dy + dz*dz;
      if (d2 < best_d2) { best_d2 = d2; best = (int)i; }
    }
    if (best < 0) return;
    const LEAP_HAND *hand = &te->pHands[best];

    // 1) absolute position: map to arm frame (meters)
    double palm_arm_m[3];
    map_mm_to_m(&hand->palm.position, palm_arm_m);

    // 2) compute desired flange orientation (no smoothing)
    double n_arm[3], d_arm[3];
    map_dir_leap_to_arm(&hand->palm.normal, n_arm);
    map_dir_leap_to_arm(&hand->palm.direction, d_arm);
    vnormalize(n_arm); vnormalize(d_arm);

    // arm bone forward (if valid)
    double arm_prev[3], arm_next[3], arm_fwd[3];
    map_mm_to_m(&hand->arm.prev_joint, arm_prev);
    map_mm_to_m(&hand->arm.next_joint, arm_next);
    vsub(arm_next, arm_prev, arm_fwd);
    vnormalize(arm_fwd); // may fail but it's fine

    // axis = normalize(n x d)
    double axis[3]; vcross(n_arm, d_arm, axis);
    bool axis_ok = vnormalize(axis);
    if (!axis_ok) {
      // try cross(n, arm_fwd)
      vcross(n_arm, arm_fwd, axis);
      axis_ok = vnormalize(axis);
    }
    if (!axis_ok) {
      // fallback pick any vector perpendicular-ish to n
      double cand[3] = {1.0,0.0,0.0};
      if (std::fabs(vdot(cand, n_arm)) > 0.9) { cand[0]=0.0; cand[1]=1.0; cand[2]=0.0; }
      vcross(n_arm, cand, axis);
      if (!vnormalize(axis)) { axis[0]=1.0; axis[1]=0.0; axis[2]=0.0; axis_ok = true; }
    }

    double cand_plus[3], cand_minus[3];
    rodrigues_rotate(n_arm, axis, ANGLE_DEG*M_PI/180.0, cand_plus);
    rodrigues_rotate(n_arm, axis, -ANGLE_DEG*M_PI/180.0, cand_minus);
    vnormalize(cand_plus); vnormalize(cand_minus);

    double dotp = vdot(cand_plus, arm_fwd);
    double dotm = vdot(cand_minus, arm_fwd);
    double chosen[3];
    if (dotp >= dotm) vcopy(cand_plus, chosen); else vcopy(cand_minus, chosen);

    double R[3][3];
    build_rotation_from_axis_chosen(axis, chosen, R);

    double rx_rad, ry_rad, rz_rad;
    rotmat_to_euler_zyx(R, rx_rad, ry_rad, rz_rad);

    long long RX_md = (long long)llround(rx_rad * RAD2DEG * MILLIDEG);
    long long RY_md = (long long)llround(ry_rad * RAD2DEG * MILLIDEG);
    long long RZ_md = (long long)llround(rz_rad * RAD2DEG * MILLIDEG);

    // publish
    auto msg_out = handpose_interfaces::msg::HandFlange();
    msg_out.header.stamp = this->now();
    msg_out.header.frame_id = frame_id_;
    msg_out.hand_id = static_cast<int64_t>(hand->id);
    msg_out.frame_id = te->tracking_frame_id; // uint64 tracking frame id from Leap

    // absolute position (m), mapped to arm frame
    msg_out.x = palm_arm_m[0];
    msg_out.y = palm_arm_m[1];
    msg_out.z = palm_arm_m[2];

    msg_out.rx_millideg = RX_md;
    msg_out.ry_millideg = RY_md;
    msg_out.rz_millideg = RZ_md;

    msg_out.pinch_strength = hand->pinch_strength;

    pub_->publish(msg_out);
  }

  rclcpp::Publisher<handpose_interfaces::msg::HandFlange>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::string frame_id_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  try {
    auto node = std::make_shared<LeapPublisherNode>();
    rclcpp::spin(node);
  } catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  rclcpp::shutdown();
  return 0;
}
