// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from handpose_publisher:msg/HandFlange.idl
// generated code does not contain a copyright notice

#ifndef HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__STRUCT_HPP_
#define HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__handpose_publisher__msg__HandFlange __attribute__((deprecated))
#else
# define DEPRECATED__handpose_publisher__msg__HandFlange __declspec(deprecated)
#endif

namespace handpose_publisher
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct HandFlange_
{
  using Type = HandFlange_<ContainerAllocator>;

  explicit HandFlange_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->hand_id = 0ll;
      this->frame_id = 0ull;
      this->x = 0.0;
      this->y = 0.0;
      this->z = 0.0;
      this->rx_millideg = 0ll;
      this->ry_millideg = 0ll;
      this->rz_millideg = 0ll;
      this->pinch_strength = 0.0f;
    }
  }

  explicit HandFlange_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->hand_id = 0ll;
      this->frame_id = 0ull;
      this->x = 0.0;
      this->y = 0.0;
      this->z = 0.0;
      this->rx_millideg = 0ll;
      this->ry_millideg = 0ll;
      this->rz_millideg = 0ll;
      this->pinch_strength = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _hand_id_type =
    int64_t;
  _hand_id_type hand_id;
  using _frame_id_type =
    uint64_t;
  _frame_id_type frame_id;
  using _x_type =
    double;
  _x_type x;
  using _y_type =
    double;
  _y_type y;
  using _z_type =
    double;
  _z_type z;
  using _rx_millideg_type =
    int64_t;
  _rx_millideg_type rx_millideg;
  using _ry_millideg_type =
    int64_t;
  _ry_millideg_type ry_millideg;
  using _rz_millideg_type =
    int64_t;
  _rz_millideg_type rz_millideg;
  using _pinch_strength_type =
    float;
  _pinch_strength_type pinch_strength;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__hand_id(
    const int64_t & _arg)
  {
    this->hand_id = _arg;
    return *this;
  }
  Type & set__frame_id(
    const uint64_t & _arg)
  {
    this->frame_id = _arg;
    return *this;
  }
  Type & set__x(
    const double & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const double & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__z(
    const double & _arg)
  {
    this->z = _arg;
    return *this;
  }
  Type & set__rx_millideg(
    const int64_t & _arg)
  {
    this->rx_millideg = _arg;
    return *this;
  }
  Type & set__ry_millideg(
    const int64_t & _arg)
  {
    this->ry_millideg = _arg;
    return *this;
  }
  Type & set__rz_millideg(
    const int64_t & _arg)
  {
    this->rz_millideg = _arg;
    return *this;
  }
  Type & set__pinch_strength(
    const float & _arg)
  {
    this->pinch_strength = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    handpose_publisher::msg::HandFlange_<ContainerAllocator> *;
  using ConstRawPtr =
    const handpose_publisher::msg::HandFlange_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<handpose_publisher::msg::HandFlange_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<handpose_publisher::msg::HandFlange_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      handpose_publisher::msg::HandFlange_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<handpose_publisher::msg::HandFlange_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      handpose_publisher::msg::HandFlange_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<handpose_publisher::msg::HandFlange_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<handpose_publisher::msg::HandFlange_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<handpose_publisher::msg::HandFlange_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__handpose_publisher__msg__HandFlange
    std::shared_ptr<handpose_publisher::msg::HandFlange_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__handpose_publisher__msg__HandFlange
    std::shared_ptr<handpose_publisher::msg::HandFlange_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const HandFlange_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->hand_id != other.hand_id) {
      return false;
    }
    if (this->frame_id != other.frame_id) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->z != other.z) {
      return false;
    }
    if (this->rx_millideg != other.rx_millideg) {
      return false;
    }
    if (this->ry_millideg != other.ry_millideg) {
      return false;
    }
    if (this->rz_millideg != other.rz_millideg) {
      return false;
    }
    if (this->pinch_strength != other.pinch_strength) {
      return false;
    }
    return true;
  }
  bool operator!=(const HandFlange_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct HandFlange_

// alias to use template instance with default allocator
using HandFlange =
  handpose_publisher::msg::HandFlange_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace handpose_publisher

#endif  // HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__STRUCT_HPP_
