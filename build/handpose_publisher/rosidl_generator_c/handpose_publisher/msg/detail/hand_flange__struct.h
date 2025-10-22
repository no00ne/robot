// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from handpose_publisher:msg/HandFlange.idl
// generated code does not contain a copyright notice

#ifndef HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__STRUCT_H_
#define HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/HandFlange in the package handpose_publisher.
typedef struct handpose_publisher__msg__HandFlange
{
  std_msgs__msg__Header header;
  int64_t hand_id;
  uint64_t frame_id;
  /// hand absolute position in arm frame (m)
  double x;
  double y;
  double z;
  int64_t rx_millideg;
  int64_t ry_millideg;
  int64_t rz_millideg;
  float pinch_strength;
} handpose_publisher__msg__HandFlange;

// Struct for a sequence of handpose_publisher__msg__HandFlange.
typedef struct handpose_publisher__msg__HandFlange__Sequence
{
  handpose_publisher__msg__HandFlange * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} handpose_publisher__msg__HandFlange__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HANDPOSE_PUBLISHER__MSG__DETAIL__HAND_FLANGE__STRUCT_H_
