cmake_minimum_required(VERSION 3.21)
project(TaskManager)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TaskManager
        DynamicArray.h
        main.cpp
        Repository.cpp
        Repository.h
        Services.cpp
        Services.h
        Task.cpp
        Task.h
        Ui.cpp
        Ui.h
        Test.h
        Test.cpp)
