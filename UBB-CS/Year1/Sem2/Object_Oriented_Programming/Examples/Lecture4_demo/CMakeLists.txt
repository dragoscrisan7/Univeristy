cmake_minimum_required(VERSION 3.21)
project(Lecture4_demo)

set(CMAKE_CXX_STANDARD 14)

include_directories(Lecture4_demo)

add_executable(Lecture4_demo
        Lecture4_demo_STL/stl_demo.cpp)
