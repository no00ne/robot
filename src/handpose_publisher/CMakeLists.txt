cmake_minimum_required(VERSION 3.8)
project(handpose_publisher LANGUAGES C CXX)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# generate message
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/HandFlange.msg"
  DEPENDENCIES std_msgs
)

# export runtime dep
ament_export_dependencies(rosidl_default_runtime)

# get typesupport target variable (may create rosidl_typesupport_cpp_target)
rosidl_get_typesupport_target(rosidl_typesupport_cpp_target ${PROJECT_NAME} "rosidl_typesupport_cpp")

# LEAP SDK include/lib (can override with env)
if(DEFINED ENV{LEAP_INCLUDE})
  set(LEAP_INCLUDE $ENV{LEAP_INCLUDE})
else()
  if(WIN32)
    set(LEAP_INCLUDE "C:/Program Files/Ultraleap/LeapSDK/include")
  else()
    set(LEAP_INCLUDE "/usr/include")
  endif()
endif()

if(DEFINED ENV{LEAP_LIBDIR})
  set(LEAP_LIBDIR $ENV{LEAP_LIBDIR})
else()
  if(WIN32)
    set(LEAP_LIBDIR "C:/Program Files/Ultraleap/LeapSDK/lib/x64")
  else()
    set(LEAP_LIBDIR "/opt/ultraleap/LeapSDK/lib")
  endif()
endif()

message(STATUS "LEAP_INCLUDE = ${LEAP_INCLUDE}")
message(STATUS "LEAP_LIBDIR  = ${LEAP_LIBDIR}")

find_path(LEAPC_INCLUDE_DIR LeapC.h HINTS ${LEAP_INCLUDE})
find_library(LEAPC_LIB NAMES LeapC LeapC.lib PATHS ${LEAP_LIBDIR} NO_DEFAULT_PATH)

if(LEAPC_INCLUDE_DIR)
  message(STATUS "Found LeapC include: ${LEAPC_INCLUDE_DIR}")
else()
  message(WARNING "LeapC header not found in ${LEAP_INCLUDE}")
endif()

if(LEAPC_LIB)
  message(STATUS "Found LeapC library: ${LEAPC_LIB}")
else()
  message(WARNING "LeapC library not found in ${LEAP_LIBDIR}")
endif()

# includes (generated headers are in build dir)
include_directories(
  include
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/rosidl_typesupport_cpp>
)

if(LEAPC_INCLUDE_DIR)
  include_directories(${LEAPC_INCLUDE_DIR})
endif()

# executable
add_executable(leap_handpose_publisher src/leap_handpose_publisher.cpp)

# Only add dependencies if the exported targets variable exists and has content
# ${PROJECT_NAME}_EXPORTED_TARGETS is produced by rosidl_generate_interfaces
if(DEFINED ${PROJECT_NAME}_EXPORTED_TARGETS)
  # expand the variable's value, then add as deps
  add_dependencies(leap_handpose_publisher ${${PROJECT_NAME}_EXPORTED_TARGETS})
endif()

# link ROS deps
ament_target_dependencies(leap_handpose_publisher rclcpp std_msgs geometry_msgs)

# link rosidl typesupport if target variable was provided
if(DEFINED rosidl_typesupport_cpp_target)
  # variable holds target name string, make sure it's non-empty
  if(NOT "${rosidl_typesupport_cpp_target}" STREQUAL "")
    target_link_libraries(leap_handpose_publisher ${rosidl_typesupport_cpp_target})
  endif()
endif()

# link LeapC if found
if(LEAPC_LIB)
  target_link_libraries(leap_handpose_publisher ${LEAPC_LIB})
  if(UNIX)
    set_target_properties(leap_handpose_publisher PROPERTIES INSTALL_RPATH ${LEAP_LIBDIR})
  endif()
endif()

install(TARGETS leap_handpose_publisher
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY msg
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
