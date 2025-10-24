// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from handpose_interfaces:msg/HandFlange.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "handpose_interfaces/msg/detail/hand_flange__struct.h"
#include "handpose_interfaces/msg/detail/hand_flange__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool handpose_interfaces__msg__hand_flange__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[48];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("handpose_interfaces.msg._hand_flange.HandFlange", full_classname_dest, 47) == 0);
  }
  handpose_interfaces__msg__HandFlange * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // hand_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "hand_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->hand_id = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // frame_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "frame_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->frame_id = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // x
    PyObject * field = PyObject_GetAttrString(_pymsg, "x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->x = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // y
    PyObject * field = PyObject_GetAttrString(_pymsg, "y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->y = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // z
    PyObject * field = PyObject_GetAttrString(_pymsg, "z");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->z = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // rx_millideg
    PyObject * field = PyObject_GetAttrString(_pymsg, "rx_millideg");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->rx_millideg = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // ry_millideg
    PyObject * field = PyObject_GetAttrString(_pymsg, "ry_millideg");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->ry_millideg = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // rz_millideg
    PyObject * field = PyObject_GetAttrString(_pymsg, "rz_millideg");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->rz_millideg = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // pinch_strength
    PyObject * field = PyObject_GetAttrString(_pymsg, "pinch_strength");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->pinch_strength = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * handpose_interfaces__msg__hand_flange__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of HandFlange */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("handpose_interfaces.msg._hand_flange");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "HandFlange");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  handpose_interfaces__msg__HandFlange * ros_message = (handpose_interfaces__msg__HandFlange *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // hand_id
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->hand_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "hand_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // frame_id
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->frame_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "frame_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // z
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->z);
    {
      int rc = PyObject_SetAttrString(_pymessage, "z", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rx_millideg
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->rx_millideg);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rx_millideg", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ry_millideg
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->ry_millideg);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ry_millideg", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rz_millideg
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->rz_millideg);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rz_millideg", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pinch_strength
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->pinch_strength);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pinch_strength", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
