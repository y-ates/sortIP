cmake_minimum_required (VERSION 2.6)
list( APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
      
project (sortIP)

# The version number.
set (sortIP_VERSION_MAJOR 1)
set (sortIP_VERSION_MINOR 0)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/sortIP.h.in"
  "${PROJECT_BINARY_DIR}/sortIP.h"
  )
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")
 
# add the executable
add_executable(sortIP main.cpp sortIP.cpp)