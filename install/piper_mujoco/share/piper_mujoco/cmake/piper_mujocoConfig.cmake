# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_piper_mujoco_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED piper_mujoco_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(piper_mujoco_FOUND FALSE)
  elseif(NOT piper_mujoco_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(piper_mujoco_FOUND FALSE)
  endif()
  return()
endif()
set(_piper_mujoco_CONFIG_INCLUDED TRUE)

# output package information
if(NOT piper_mujoco_FIND_QUIETLY)
  message(STATUS "Found piper_mujoco: 0.0.0 (${piper_mujoco_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'piper_mujoco' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${piper_mujoco_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(piper_mujoco_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${piper_mujoco_DIR}/${_extra}")
endforeach()
