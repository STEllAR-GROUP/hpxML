cmake_minimum_required (VERSION 2.8.11)
project (Regression)

find_package (Eigen3 REQUIRED NO_MODULE)

add_executable (regression main.cpp)