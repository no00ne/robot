// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from handpose_publisher:msg/HandFlange.idl
// generated code does not contain a copyright notice

#ifndef HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "handpose_publisher/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "handpose_publisher/msg/detail/hand_flange__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace handpose_publisher
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_handpose_publisher
cdr_serialize(
  const handpose_publisher::msg::HandFlange & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_handpose_publisher
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  handpose_publisher::msg::HandFlange & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_handpose_publisher
get_serialized_size(
  const handpose_publisher::msg::HandFlange & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_handpose_publisher
max_serialized_size_HandFlange(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace handpose_publisher

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_handpose_publisher
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, handpose_publisher, msg, HandFlange)();

#ifdef __cplusplus
}
#endif

#endif  // HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
