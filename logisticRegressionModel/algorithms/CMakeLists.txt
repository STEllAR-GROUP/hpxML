cmake_minimum_required (VERSION 2.8.11)
project (Regression)

find_package (Eigen3 REQUIRED NO_MODULE)

include_directories("/usr/include/")
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable (regression main.cpp)
