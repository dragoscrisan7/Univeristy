cmake_minimum_required(VERSION 3.21)
project(Seminar2_911)

set(CMAKE_CXX_STANDARD 14)

include_directories(Seminar2_911)

add_executable(Seminar2_911
        Seminar2_911/DynamicVector.cpp
        Seminar2_911/DynamicVector.h
        Seminar2_911/main.cpp
        Seminar2_911/Repository.cpp
        Seminar2_911/Repository.h
        Seminar2_911/Service.cpp
        Seminar2_911/Service.h
        Seminar2_911/Song.cpp
        Seminar2_911/Song.h)
