cmake_minimum_required(VERSION 3.21)
project(PregatireDragos)

set(CMAKE_CXX_STANDARD 14)

add_executable(PregatireDragos main.cpp
        Building.cpp
        Building.h
        House.cpp
        House.h
        Block.cpp
        Block.h
        Service.cpp
        Service.h
        ui.cpp
        ui.h)
