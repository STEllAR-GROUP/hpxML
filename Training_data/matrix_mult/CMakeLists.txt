cmake_minimum_required(VERSION 2.8.12)
project(main CXX)

set(HPX_ROOT "/path/to/HPX/build")
set(HPX_DIR "${HPX_ROOT}/lib/cmake/HPX")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(HPX)
find_package(Boost REQUIRED)


include_directories(${HPX_INCLUDE_DIR})
link_directories(${HPX_LIBRARY_DIR})

set(SOURCE_FILES main.cpp)
add_hpx_executable(name
    ESSENTIAL
    SOURCES ${SOURCE_FILES}
    COMPONENT_DEPENDENCIES iostreams)

target_link_libraries(name_exe -L${Boost_LIBRARY_DIRS})
