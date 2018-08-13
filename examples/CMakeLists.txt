cmake_minimum_required(VERSION 2.8.12)
project(main CXX)

#set(HPX_ROOT "/path/to/HPX/build")
set(HPX_DIR "${HPX_ROOT}/lib/cmake/HPX")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(HPX)

include_directories(${HPX_INCLUDE_DIR})
include_directories(../include)
link_directories(${HPX_LIBRARY_DIR})


add_hpx_executable(stencil
    ESSENTIAL
    SOURCES stencil/main.cpp
    COMPONENT_DEPENDENCIES iostreams)
    
add_hpx_executable(stream
    ESSENTIAL
    SOURCES stream/main.cpp
    COMPONENT_DEPENDENCIES iostreams)
    
add_hpx_executable(matrix_mult
    ESSENTIAL
    SOURCES matrix_mult/main.cpp
    COMPONENT_DEPENDENCIES iostreams)
