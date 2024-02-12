cmake_minimum_required(VERSION 3.21)
project(Lecture6_demo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lecture6_demo
        Animal.cpp
        Animal.h
        Dog.cpp
        Dog.h
        main.cpp
        Penguin.cpp
        Penguin.h)
