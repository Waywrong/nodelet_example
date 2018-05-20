cmake_minimum_required(VERSION 2.8.3)  
project(nodelet_test_pkg)  
  
find_package(catkin REQUIRED COMPONENTS nodelet roscpp std_msgs)#  
  
## Setup include directories  
include_directories(${catkin_INCLUDE_DIRS})  
  
catkin_package(  
)  
  
add_library(nodelet_test_lib src/plus.cpp)  
target_link_libraries(nodelet_test_lib ${catkin_LIBRARIES})
