cmake_minimum_required(VERSION 2.8.3)
project(nodelet_test_pkg)

## Add support for C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS 
  nodelet 
  roscpp 
  std_msgs
  grid_map_ros
  grid_map_cv
  grid_map_msgs
  grid_map_core
)

## Setup include directories
include_directories(
  include/
  ${catkin_INCLUDE_DIRS}
)

catkin_package(
  LIBRARIES nodelet_test_pkg
  CATKIN_DEPENDS nodelet roscpp std_msgs
)

## Create the nodelet tutorial library
add_library(nodelet_test_lib src/plus.cpp)
target_link_libraries(nodelet_test_lib ${catkin_LIBRARIES})
if(catkin_EXPORTED_LIBRARIES)
  add_dependencies(nodelet_test_lib ${catkin_EXPORTED_LIBRARIES})
endif()

## Mark the nodelet library for installations
install(TARGETS nodelet_test_lib
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

## Mark other files for installation (e.g. launch and bag files, etc.)
install(FILES plugins/nodelet_test.xml plus_default.yaml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
