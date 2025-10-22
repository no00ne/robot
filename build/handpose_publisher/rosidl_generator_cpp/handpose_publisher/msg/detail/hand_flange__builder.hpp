// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from handpose_publisher:msg/HandFlange.idl
// generated code does not contain a copyright notice

#ifndef HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__BUILDER_HPP_
#define HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "handpose_publisher/msg/detail/hand_flange__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace handpose_publisher
{

namespace msg
{

namespace builder
{

class Init_HandFlange_pinch_strength
{
public:
  explicit Init_HandFlange_pinch_strength(::handpose_publisher::msg::HandFlange & msg)
  : msg_(msg)
  {}
  ::handpose_publisher::msg::HandFlange pinch_strength(::handpose_publisher::msg::HandFlange::_pinch_strength_type arg)
  {
    msg_.pinch_strength = std::move(arg);
    return std::move(msg_);
  }

private:
  ::handpose_publisher::msg::HandFlange msg_;
};

class Init_HandFlange_rz_millideg
{
public:
  explicit Init_HandFlange_rz_millideg(::handpose_publisher::msg::HandFlange & msg)
  : msg_(msg)
  {}
  Init_HandFlange_pinch_strength rz_millideg(::handpose_publisher::msg::HandFlange::_rz_millideg_type arg)
  {
    msg_.rz_millideg = std::move(arg);
    return Init_HandFlange_pinch_strength(msg_);
  }

private:
  ::handpose_publisher::msg::HandFlange msg_;
};

class Init_HandFlange_ry_millideg
{
public:
  explicit Init_HandFlange_ry_millideg(::handpose_publisher::msg::HandFlange & msg)
  : msg_(msg)
  {}
  Init_HandFlange_rz_millideg ry_millideg(::handpose_publisher::msg::HandFlange::_ry_millideg_type arg)
  {
    msg_.ry_millideg = std::move(arg);
    return Init_HandFlange_rz_millideg(msg_);
  }

private:
  ::handpose_publisher::msg::HandFlange msg_;
};

class Init_HandFlange_rx_millideg
{
public:
  explicit Init_HandFlange_rx_millideg(::handpose_publisher::msg::HandFlange & msg)
  : msg_(msg)
  {}
  Init_HandFlange_ry_millideg rx_millideg(::handpose_publisher::msg::HandFlange::_rx_millideg_type arg)
  {
    msg_.rx_millideg = std::move(arg);
    return Init_HandFlange_ry_millideg(msg_);
  }

private:
  ::handpose_publisher::msg::HandFlange msg_;
};

class Init_HandFlange_z
{
public:
  explicit Init_HandFlange_z(::handpose_publisher::msg::HandFlange & msg)
  : msg_(msg)
  {}
  Init_HandFlange_rx_millideg z(::handpose_publisher::msg::HandFlange::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_HandFlange_rx_millideg(msg_);
  }

private:
  ::handpose_publisher::msg::HandFlange msg_;
};

class Init_HandFlange_y
{
public:
  explicit Init_HandFlange_y(::handpose_publisher::msg::HandFlange & msg)
  : msg_(msg)
  {}
  Init_HandFlange_z y(::handpose_publisher::msg::HandFlange::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_HandFlange_z(msg_);
  }

private:
  ::handpose_publisher::msg::HandFlange msg_;
};

class Init_HandFlange_x
{
public:
  explicit Init_HandFlange_x(::handpose_publisher::msg::HandFlange & msg)
  : msg_(msg)
  {}
  Init_HandFlange_y x(::handpose_publisher::msg::HandFlange::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_HandFlange_y(msg_);
  }

private:
  ::handpose_publisher::msg::HandFlange msg_;
};

class Init_HandFlange_frame_id
{
public:
  explicit Init_HandFlange_frame_id(::handpose_publisher::msg::HandFlange & msg)
  : msg_(msg)
  {}
  Init_HandFlange_x frame_id(::handpose_publisher::msg::HandFlange::_frame_id_type arg)
  {
    msg_.frame_id = std::move(arg);
    return Init_HandFlange_x(msg_);
  }

private:
  ::handpose_publisher::msg::HandFlange msg_;
};

class Init_HandFlange_hand_id
{
public:
  explicit Init_HandFlange_hand_id(::handpose_publisher::msg::HandFlange & msg)
  : msg_(msg)
  {}
  Init_HandFlange_frame_id hand_id(::handpose_publisher::msg::HandFlange::_hand_id_type arg)
  {
    msg_.hand_id = std::move(arg);
    return Init_HandFlange_frame_id(msg_);
  }

private:
  ::handpose_publisher::msg::HandFlange msg_;
};

class Init_HandFlange_header
{
public:
  Init_HandFlange_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandFlange_hand_id header(::handpose_publisher::msg::HandFlange::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_HandFlange_hand_id(msg_);
  }

private:
  ::handpose_publisher::msg::HandFlange msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::handpose_publisher::msg::HandFlange>()
{
  return handpose_publisher::msg::builder::Init_HandFlange_header();
}

}  // namespace handpose_publisher

#endif  // HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__BUILDER_HPP_
