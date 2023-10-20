cmake_minimum_required(VERSION 3.21)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab1 main.cpp

        utils/Utils.cpp
        utils/Utils.h
        checks/Checks.cpp
        checks/Checks.h)
