cmake_minimum_required(VERSION 3.21)
project(Example_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Example_files
        Repository.cpp
        Repository.h
        Song.cpp
        Song.h)
