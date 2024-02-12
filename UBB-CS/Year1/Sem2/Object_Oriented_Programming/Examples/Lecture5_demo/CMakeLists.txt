cmake_minimum_required(VERSION 3.21)
project(Lecture5_demo)

set(CMAKE_CXX_STANDARD 14)

include_directories(Lecture5_demo)

add_executable(Lecture5_demo
        Lecture5_demo/Animal.cpp
        Lecture5_demo/Animal.h
        Lecture5_demo/Dog.cpp
        Lecture5_demo/Dog.h
        Lecture5_demo/main.cpp
        Lecture5_demo/Penguin.cpp
        Lecture5_demo/Penguin.h
        MultipleInheritance/main.cpp)
