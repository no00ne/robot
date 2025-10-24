// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from handpose_interfaces:msg/HandFlange.idl
// generated code does not contain a copyright notice
#include "handpose_interfaces/msg/detail/hand_flange__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
handpose_interfaces__msg__HandFlange__init(handpose_interfaces__msg__HandFlange * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    handpose_interfaces__msg__HandFlange__fini(msg);
    return false;
  }
  // hand_id
  // frame_id
  // x
  // y
  // z
  // rx_millideg
  // ry_millideg
  // rz_millideg
  // pinch_strength
  return true;
}

void
handpose_interfaces__msg__HandFlange__fini(handpose_interfaces__msg__HandFlange * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // hand_id
  // frame_id
  // x
  // y
  // z
  // rx_millideg
  // ry_millideg
  // rz_millideg
  // pinch_strength
}

bool
handpose_interfaces__msg__HandFlange__are_equal(const handpose_interfaces__msg__HandFlange * lhs, const handpose_interfaces__msg__HandFlange * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // hand_id
  if (lhs->hand_id != rhs->hand_id) {
    return false;
  }
  // frame_id
  if (lhs->frame_id != rhs->frame_id) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // z
  if (lhs->z != rhs->z) {
    return false;
  }
  // rx_millideg
  if (lhs->rx_millideg != rhs->rx_millideg) {
    return false;
  }
  // ry_millideg
  if (lhs->ry_millideg != rhs->ry_millideg) {
    return false;
  }
  // rz_millideg
  if (lhs->rz_millideg != rhs->rz_millideg) {
    return false;
  }
  // pinch_strength
  if (lhs->pinch_strength != rhs->pinch_strength) {
    return false;
  }
  return true;
}

bool
handpose_interfaces__msg__HandFlange__copy(
  const handpose_interfaces__msg__HandFlange * input,
  handpose_interfaces__msg__HandFlange * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // hand_id
  output->hand_id = input->hand_id;
  // frame_id
  output->frame_id = input->frame_id;
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // z
  output->z = input->z;
  // rx_millideg
  output->rx_millideg = input->rx_millideg;
  // ry_millideg
  output->ry_millideg = input->ry_millideg;
  // rz_millideg
  output->rz_millideg = input->rz_millideg;
  // pinch_strength
  output->pinch_strength = input->pinch_strength;
  return true;
}

handpose_interfaces__msg__HandFlange *
handpose_interfaces__msg__HandFlange__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  handpose_interfaces__msg__HandFlange * msg = (handpose_interfaces__msg__HandFlange *)allocator.allocate(sizeof(handpose_interfaces__msg__HandFlange), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(handpose_interfaces__msg__HandFlange));
  bool success = handpose_interfaces__msg__HandFlange__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
handpose_interfaces__msg__HandFlange__destroy(handpose_interfaces__msg__HandFlange * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    handpose_interfaces__msg__HandFlange__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
handpose_interfaces__msg__HandFlange__Sequence__init(handpose_interfaces__msg__HandFlange__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  handpose_interfaces__msg__HandFlange * data = NULL;

  if (size) {
    data = (handpose_interfaces__msg__HandFlange *)allocator.zero_allocate(size, sizeof(handpose_interfaces__msg__HandFlange), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = handpose_interfaces__msg__HandFlange__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        handpose_interfaces__msg__HandFlange__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
handpose_interfaces__msg__HandFlange__Sequence__fini(handpose_interfaces__msg__HandFlange__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      handpose_interfaces__msg__HandFlange__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

handpose_interfaces__msg__HandFlange__Sequence *
handpose_interfaces__msg__HandFlange__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  handpose_interfaces__msg__HandFlange__Sequence * array = (handpose_interfaces__msg__HandFlange__Sequence *)allocator.allocate(sizeof(handpose_interfaces__msg__HandFlange__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = handpose_interfaces__msg__HandFlange__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
handpose_interfaces__msg__HandFlange__Sequence__destroy(handpose_interfaces__msg__HandFlange__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    handpose_interfaces__msg__HandFlange__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
handpose_interfaces__msg__HandFlange__Sequence__are_equal(const handpose_interfaces__msg__HandFlange__Sequence * lhs, const handpose_interfaces__msg__HandFlange__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!handpose_interfaces__msg__HandFlange__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
handpose_interfaces__msg__HandFlange__Sequence__copy(
  const handpose_interfaces__msg__HandFlange__Sequence * input,
  handpose_interfaces__msg__HandFlange__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(handpose_interfaces__msg__HandFlange);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    handpose_interfaces__msg__HandFlange * data =
      (handpose_interfaces__msg__HandFlange *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!handpose_interfaces__msg__HandFlange__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          handpose_interfaces__msg__HandFlange__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!handpose_interfaces__msg__HandFlange__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
