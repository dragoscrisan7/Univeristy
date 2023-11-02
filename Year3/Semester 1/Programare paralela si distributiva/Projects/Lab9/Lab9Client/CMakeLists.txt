cmake_minimum_required(VERSION 3.21)
project(Lab9Client)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab9Client main.cpp)

if(WIN32)
    target_link_libraries(Lab9Client wsock32 ws2_32)
endif()