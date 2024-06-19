cmake_minimum_required(VERSION 3.21)
project(PregatireTest2)

set(CMAKE_CXX_STANDARD 14)

add_executable(PregatireTest2 main.cpp
        Building.cpp
        Building.h
        Block.cpp
        Block.h House.cpp House.h Service.cpp Service.h UserInterface.cpp UserInterface.h)
