// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from handpose_publisher:msg/HandFlange.idl
// generated code does not contain a copyright notice

#ifndef HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__TRAITS_HPP_
#define HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "handpose_publisher/msg/detail/hand_flange__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace handpose_publisher
{

namespace msg
{

inline void to_flow_style_yaml(
  const HandFlange & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: hand_id
  {
    out << "hand_id: ";
    rosidl_generator_traits::value_to_yaml(msg.hand_id, out);
    out << ", ";
  }

  // member: frame_id
  {
    out << "frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_id, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: z
  {
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << ", ";
  }

  // member: rx_millideg
  {
    out << "rx_millideg: ";
    rosidl_generator_traits::value_to_yaml(msg.rx_millideg, out);
    out << ", ";
  }

  // member: ry_millideg
  {
    out << "ry_millideg: ";
    rosidl_generator_traits::value_to_yaml(msg.ry_millideg, out);
    out << ", ";
  }

  // member: rz_millideg
  {
    out << "rz_millideg: ";
    rosidl_generator_traits::value_to_yaml(msg.rz_millideg, out);
    out << ", ";
  }

  // member: pinch_strength
  {
    out << "pinch_strength: ";
    rosidl_generator_traits::value_to_yaml(msg.pinch_strength, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const HandFlange & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: hand_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hand_id: ";
    rosidl_generator_traits::value_to_yaml(msg.hand_id, out);
    out << "\n";
  }

  // member: frame_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_id, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << "\n";
  }

  // member: rx_millideg
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rx_millideg: ";
    rosidl_generator_traits::value_to_yaml(msg.rx_millideg, out);
    out << "\n";
  }

  // member: ry_millideg
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ry_millideg: ";
    rosidl_generator_traits::value_to_yaml(msg.ry_millideg, out);
    out << "\n";
  }

  // member: rz_millideg
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rz_millideg: ";
    rosidl_generator_traits::value_to_yaml(msg.rz_millideg, out);
    out << "\n";
  }

  // member: pinch_strength
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pinch_strength: ";
    rosidl_generator_traits::value_to_yaml(msg.pinch_strength, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const HandFlange & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace handpose_publisher

namespace rosidl_generator_traits
{

[[deprecated("use handpose_publisher::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const handpose_publisher::msg::HandFlange & msg,
  std::ostream & out, size_t indentation = 0)
{
  handpose_publisher::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use handpose_publisher::msg::to_yaml() instead")]]
inline std::string to_yaml(const handpose_publisher::msg::HandFlange & msg)
{
  return handpose_publisher::msg::to_yaml(msg);
}

template<>
inline const char * data_type<handpose_publisher::msg::HandFlange>()
{
  return "handpose_publisher::msg::HandFlange";
}

template<>
inline const char * name<handpose_publisher::msg::HandFlange>()
{
  return "handpose_publisher/msg/HandFlange";
}

template<>
struct has_fixed_size<handpose_publisher::msg::HandFlange>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<handpose_publisher::msg::HandFlange>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<handpose_publisher::msg::HandFlange>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__TRAITS_HPP_
