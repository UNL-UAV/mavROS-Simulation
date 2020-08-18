cmake_minimum_required(VERSION 3.0.2)
project(examples)

find_package(catkin REQUIRED COMPONENTS
  mavros
  roscpp
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(takeoff_example src/offb_node.cpp)
target_link_libraries(takeoff_example ${catkin_LIBRARIES})
add_dependencies(takeoff_example ${catkin_EXPORTED_TARGETS})

add_executable(land_example src/land_node.cpp)
target_link_libraries(land_example ${catkin_LIBRARIES})
add_dependencies(land_example ${catkin_EXPORTED_TARGETS})