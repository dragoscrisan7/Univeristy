cmake_minimum_required(VERSION 3.21)
project(Seminar3_Week1_stub)

set(CMAKE_CXX_STANDARD 14)

include_directories(Seminar3_Week1_stub)

add_executable(Seminar3_Week1_stub
        Seminar3_Week1_stub/Controller.cpp
        Seminar3_Week1_stub/Controller.h
        Seminar3_Week1_stub/DynamicVector.h
        Seminar3_Week1_stub/main.cpp
        Seminar3_Week1_stub/Repository.cpp
        Seminar3_Week1_stub/Repository.h
        Seminar3_Week1_stub/Song.cpp
        Seminar3_Week1_stub/Song.h
        Seminar3_Week1_stub/Tests.cpp
        Seminar3_Week1_stub/Tests.h
        Seminar3_Week1_stub/UI.cpp
        Seminar3_Week1_stub/UI.h)
