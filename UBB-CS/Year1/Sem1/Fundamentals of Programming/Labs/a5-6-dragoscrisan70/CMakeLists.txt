cmake_minimum_required(VERSION 3.21)
project(a5_6_dragoscrisan7)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(a5_6_dragoscrisan7
        Dog.cpp
        Dog.h
        Dynamic_array.h
        Repository.cpp
        Repository.h
        Service.h
        Service.cpp
        UserRepo.h
        UserRepo.cpp
        UserService.h
        UserService.cpp
        UI.h
        UI.cpp
        main.cpp
        Test.h
        Test.cpp)
