cmake_minimum_required(VERSION 2.8.3)
project(atc)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(GUROBI REQUIRED)

if(GUROBI_FOUND)
  message(STATUS "GUROBI FOUND")
else(GUROBI_FOUND)
  message(FATAL_ERROR "!!! GUROBI NOT FOUND !!!")
endif(GUROBI_FOUND)

include_directories(
 include
  #${catkin_INCLUDE_DIRS}
  ${GUROBI_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node src/atc_node.cpp)

target_link_libraries(${PROJECT_NAME}_node
  #${catkin_LIBRARIES}
  ${GUROBI_LIBRARIES}
)