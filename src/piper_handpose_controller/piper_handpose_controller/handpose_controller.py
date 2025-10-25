#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
handpose_controller.py
订阅:  /handpose/flange (handpose_interfaces/HandFlange)
       /end_pose_stamped (geometry_msgs/PoseStamped)
       /enable_flag (std_msgs/Bool)
发布:  /pos_cmd (piper_msgs/PosCmd) -- 位置单位 m, 角度 rad, gripper m
       /target_pose (geometry_msgs/PoseStamped) -- 可视化
首次 enable 时会发布一次 initial pose（由旧脚本的 piper 单位转换而来）
简单低通 (位置) + slerp (姿态) + 速率限制
"""
import math
from typing import Optional, Tuple

import rclpy
from rclpy.node import Node

from std_msgs.msg import Bool
from geometry_msgs.msg import PoseStamped, Pose, Quaternion, Point
from handpose_interfaces.msg import HandFlange
from piper_msgs.msg import PosCmd

# ---- math helpers (quat/euler/slerp, vector ops) ----
def euler_xyz_to_quat(roll: float, pitch: float, yaw: float) -> Tuple[float,float,float,float]:
    cr = math.cos(roll * 0.5); sr = math.sin(roll * 0.5)
    cp = math.cos(pitch * 0.5); sp = math.sin(pitch * 0.5)
    cy = math.cos(yaw * 0.5); sy = math.sin(yaw * 0.5)
    w = cr*cp*cy + sr*sp*sy
    x = sr*cp*cy - cr*sp*sy
    y = cr*sp*cy + sr*cp*sy
    z = cr*cp*sy - sr*sp*cy
    return (x,y,z,w)

def quat_normalize(q):
    x,y,z,w = q
    n = math.sqrt(x*x+y*y+z*z+w*w)
    if n < 1e-12: return (0.0,0.0,0.0,1.0)
    return (x/n,y/n,z/n,w/n)

def quat_dot(a,b):
    return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]+a[3]*b[3]

def quat_inverse(q):
    x,y,z,w = q
    return (-x,-y,-z,w)

def quat_mul(a,b):
    ax,ay,az,aw = a; bx,by,bz,bw = b
    x = aw*bx + ax*bw + ay*bz - az*by
    y = aw*by - ax*bz + ay*bw + az*bx
    z = aw*bz + ax*by - ay*bx + az*bw
    w = aw*bw - ax*bx - ay*by - az*bz
    return (x,y,z,w)

def quat_to_euler_xyz(q):
    x,y,z,w = q
    sinr_cosp = 2.0*(w*x + y*z)
    cosr_cosp = 1.0 - 2.0*(x*x + y*y)
    roll = math.atan2(sinr_cosp, cosr_cosp)
    sinp = 2.0*(w*y - z*x)
    if abs(sinp) >= 1:
        pitch = math.copysign(math.pi/2.0, sinp)
    else:
        pitch = math.asin(sinp)
    siny_cosp = 2.0*(w*z + x*y)
    cosy_cosp = 1.0 - 2.0*(y*y + z*z)
    yaw = math.atan2(siny_cosp, cosy_cosp)
    return (roll, pitch, yaw)

def slerp(a,b,t):
    ax,ay,az,aw = quat_normalize(a); bx,by,bz,bw = quat_normalize(b)
    dot = quat_dot((ax,ay,az,aw),(bx,by,bz,bw))
    if dot < 0.0:
        bx,by,bz,bw = -bx,-by,-bz,-bw
        dot = -dot
    if dot > 0.9995:
        x = ax + t*(bx-ax); y = ay + t*(by-ay); z = az + t*(bz-az); w = aw + t*(bw-aw)
        return quat_normalize((x,y,z,w))
    theta_0 = math.acos(max(min(dot,1.0),-1.0))
    theta = theta_0 * t
    sin_theta = math.sin(theta); sin_theta_0 = math.sin(theta_0)
    s0 = math.cos(theta) - dot * sin_theta / sin_theta_0
    s1 = sin_theta / sin_theta_0
    x = s0*ax + s1*bx; y = s0*ay + s1*by; z = s0*az + s1*bz; w = s0*aw + s1*bw
    return (x,y,z,w)

def vec_norm(v): return math.sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2])
def vec_sub(a,b): return (a[0]-b[0], a[1]-b[1], a[2]-b[2])
def vec_add(a,b): return (a[0]+b[0], a[1]+b[1], a[2]+b[2])
def vec_scale(a,s): return (a[0]*s, a[1]*s, a[2]*s)

# ---- Node ----
class HandposeController(Node):
    def __init__(self):
        super().__init__('handpose_controller')
        # params
        self.declare_parameter('hand_topic', '/handpose/flange')
        self.declare_parameter('end_pose_topic', '/end_pose_stamped')
        self.declare_parameter('enable_topic', '/enable_flag')
        self.declare_parameter('pos_cmd_topic', '/pos_cmd')
        self.declare_parameter('target_pose_topic', '/target_pose')

        self.declare_parameter('pos_alpha', 0.35)
        self.declare_parameter('rot_alpha', 0.35)
        self.declare_parameter('send_hz', 30.0)
        self.declare_parameter('max_lin_vel', 0.5)          # m/s
        self.declare_parameter('max_ang_deg_s', 90.0)       # deg/s
        self.declare_parameter('hand_timeout_s', 0.5)
        self.declare_parameter('k_pos', 1.0)
        self.declare_parameter('gripper_full_mm', 100.0)

        # initial piper pose (old script piper units) -> will be sent once on enable
        self._initial_piper = {'X':257384,'Y':4793,'Z':147021,'RX':-173360,'RY':65070,'RZ':-169444}

        # load params
        self.hand_topic = self.get_parameter('hand_topic').get_parameter_value().string_value
        self.end_pose_topic = self.get_parameter('end_pose_topic').get_parameter_value().string_value
        self.enable_topic = self.get_parameter('enable_topic').get_parameter_value().string_value
        self.pos_cmd_topic = self.get_parameter('pos_cmd_topic').get_parameter_value().string_value
        self.target_pose_topic = self.get_parameter('target_pose_topic').get_parameter_value().string_value

        self.pos_alpha = float(self.get_parameter('pos_alpha').get_parameter_value().double_value)
        self.rot_alpha = float(self.get_parameter('rot_alpha').get_parameter_value().double_value)
        self.send_hz = float(self.get_parameter('send_hz').get_parameter_value().double_value)
        self.max_lin_vel = float(self.get_parameter('max_lin_vel').get_parameter_value().double_value)
        self.max_ang_deg_s = float(self.get_parameter('max_ang_deg_s').get_parameter_value().double_value)
        self.hand_timeout_s = float(self.get_parameter('hand_timeout_s').get_parameter_value().double_value)
        self.k_pos = float(self.get_parameter('k_pos').get_parameter_value().double_value)
        self.gripper_full_mm = float(self.get_parameter('gripper_full_mm').get_parameter_value().double_value)

        # state
        self._last_hand_msg: Optional[HandFlange] = None
        self._last_hand_time = 0.0
        self._current_hand_id: Optional[int] = None
        self._machine_origin_pos: Optional[Tuple[float,float,float]] = None

        self._filtered_pos: Optional[Tuple[float,float,float]] = None
        self._filtered_quat = (0.0,0.0,0.0,1.0)
        self._last_sent_pos: Optional[Tuple[float,float,float]] = None
        self._last_sent_quat = (0.0,0.0,0.0,1.0)
        self._last_send_time = self.get_clock().now().nanoseconds * 1e-9

        self._enabled = False
        self._initial_sent = False

        # subs/pubs
        self.create_subscription(HandFlange, self.hand_topic, self._cb_hand, 10)
        self.create_subscription(PoseStamped, self.end_pose_topic, self._cb_endpose, 10)
        self.create_subscription(Bool, self.enable_topic, self._cb_enable, 10)

        self._pub_pos = self.create_publisher(PosCmd, self.pos_cmd_topic, 10)
        self._pub_target = self.create_publisher(PoseStamped, self.target_pose_topic, 10)

        period = 1.0 / max(1.0, self.send_hz)
        self.create_timer(period, self._timer_loop)

        self.get_logger().info("handpose_controller started: subscribe %s publish %s" % (self.hand_topic, self.pos_cmd_topic))

    # callbacks
    def _cb_hand(self, msg: HandFlange):
        # store last message
        self._last_hand_msg = msg
        self._last_hand_time = self.get_clock().now().nanoseconds * 1e-9
        # detect new hand (start)
        if self._current_hand_id is None or int(msg.hand_id) != int(self._current_hand_id):
            old = self._current_hand_id
            self._current_hand_id = int(msg.hand_id)
            self.get_logger().info(f"Hand START detected: hand_id {self._current_hand_id} (prev {old})")
            # reset filters
            self._filtered_pos = None
            self._filtered_quat = (0.0,0.0,0.0,1.0)

    def _cb_endpose(self, msg: PoseStamped):
        p = msg.pose.position
        self._machine_origin_pos = (float(p.x), float(p.y), float(p.z))

    def _cb_enable(self, msg: Bool):
        self._enabled = bool(msg.data)
        self.get_logger().info(f"Enable flag -> {self._enabled}")
        if self._enabled and not self._initial_sent:
            self._send_initial_pose_once()

    # internal
    def _send_initial_pose_once(self):
        p = self._initial_piper
        x_m = p['X'] * 1e-6
        y_m = p['Y'] * 1e-6
        z_m = p['Z'] * 1e-6
        rx = p['RX'] * (math.pi / 180000.0)
        ry = p['RY'] * (math.pi / 180000.0)
        rz = p['RZ'] * (math.pi / 180000.0)
        pc = PosCmd()
        pc.x = float(x_m); pc.y = float(y_m); pc.z = float(z_m)
        pc.roll = float(rx); pc.pitch = float(ry); pc.yaw = float(rz)
        pc.gripper = 0.0
        pc.mode1 = 1; pc.mode2 = 0
        try:
            self._pub_pos.publish(pc)
            self._initial_sent = True
            self.get_logger().info("Published initial pose (converted from piper units).")
        except Exception as e:
            self.get_logger().warn("Failed publish initial pose: %s" % str(e))

    def _now_s(self):
        return self.get_clock().now().nanoseconds * 1e-9

    # main loop
    def _timer_loop(self):
        now = self._now_s()
        if self._last_hand_msg is None:
            return
        if now - self._last_hand_time > self.hand_timeout_s:
            if self._current_hand_id is not None:
                self.get_logger().info("Hand LOST (timeout) -> clearing current hand")
                self._current_hand_id = None
            return

        hf = self._last_hand_msg
        # absolute hand pos from upstream (m)
        hand_pos = (float(hf.x), float(hf.y), float(hf.z))

        # mapping / optional scaling around machine origin
        if self._machine_origin_pos is not None and self.k_pos != 1.0:
            delta = vec_sub(hand_pos, self._machine_origin_pos)
            mapped = vec_add(self._machine_origin_pos, vec_scale(delta, self.k_pos))
            target_pos = mapped
        else:
            target_pos = hand_pos

        # orientation: upstream provides millideg RX/RY/RZ (ZYX in publisher), treat as XYZ euler here as earlier code did
        rx_rad = float(hf.rx_millideg) * (math.pi / 180000.0)
        ry_rad = float(hf.ry_millideg) * (math.pi / 180000.0)
        rz_rad = float(hf.rz_millideg) * (math.pi / 180000.0)
        new_quat = euler_xyz_to_quat(rx_rad, ry_rad, rz_rad)
        new_quat = quat_normalize(new_quat)

        # pinch -> gripper m (invert)
        pinch = max(0.0, min(1.0, float(getattr(hf, 'pinch_strength', 0.0))))
        inv_mm = (self.gripper_full_mm * (1.0 - pinch))
        gripper_m = max(0.0, inv_mm / 1000.0)
        if gripper_m > 0.08: gripper_m = 0.08

        # filtering
        if self._filtered_pos is None:
            self._filtered_pos = target_pos
            self._filtered_quat = new_quat
            if self._last_sent_pos is None:
                self._last_sent_pos = target_pos
        else:
            a = self.pos_alpha
            self._filtered_pos = (a*target_pos[0] + (1-a)*self._filtered_pos[0],
                                  a*target_pos[1] + (1-a)*self._filtered_pos[1],
                                  a*target_pos[2] + (1-a)*self._filtered_pos[2])
            self._filtered_quat = quat_normalize(slerp(self._filtered_quat, new_quat, self.rot_alpha))

        # rate limiting
        dt = max(1e-6, now - self._last_send_time)
        delta_pos = vec_sub(self._filtered_pos, self._last_sent_pos) if self._last_sent_pos is not None else (0.0,0.0,0.0)
        dist = vec_norm(delta_pos)
        max_step = self.max_lin_vel * dt
        if dist > max_step and dist > 1e-12:
            scale = max_step / dist
            delta_pos = vec_scale(delta_pos, scale)
        new_send_pos = vec_add(self._last_sent_pos, delta_pos) if self._last_sent_pos is not None else self._filtered_pos

        dq = quat_mul(quat_inverse(self._last_sent_quat), self._filtered_quat)
        dq = quat_normalize(dq)
        angle = 2.0 * math.acos(max(min(dq[3],1.0), -1.0))
        max_ang = (self.max_ang_deg_s * math.pi / 180.0) * dt
        if angle > max_ang and angle > 1e-8:
            frac = max_ang / angle
            new_send_quat = slerp(self._last_sent_quat, self._filtered_quat, frac)
        else:
            new_send_quat = self._filtered_quat

        # publish if enabled
        if self._enabled:
            pc = PosCmd()
            pc.x = float(new_send_pos[0]); pc.y = float(new_send_pos[1]); pc.z = float(new_send_pos[2])
            r,p,y = quat_to_euler_xyz(new_send_quat)
            pc.roll = float(r); pc.pitch = float(p); pc.yaw = float(y)
            pc.gripper = float(gripper_m)
            pc.mode1 = 1; pc.mode2 = 0
            try:
                self._pub_pos.publish(pc)
            except Exception as e:
                self.get_logger().warn("publish /pos_cmd failed: %s" % str(e))
            # publish target_pose for viz
            ps = PoseStamped()
            ps.header.stamp = self.get_clock().now().to_msg()
            ps.header.frame_id = 'piper_base'
            ps.pose.position = Point(x=new_send_pos[0], y=new_send_pos[1], z=new_send_pos[2])
            qx,qy,qz,qw = new_send_quat
            ps.pose.orientation = Quaternion(x=qx, y=qy, z=qz, w=qw)
            try:
                self._pub_target.publish(ps)
            except Exception:
                pass

            self._last_sent_pos = new_send_pos
            self._last_sent_quat = new_send_quat
            self._last_send_time = now
        else:
            # not enabled: update last_sent to filtered to avoid jump on enable
            self._last_sent_pos = self._filtered_pos
            self._last_sent_quat = self._filtered_quat
            self._last_send_time = now

def main(args=None):
    rclpy.init(args=args)
    node = HandposeController()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
