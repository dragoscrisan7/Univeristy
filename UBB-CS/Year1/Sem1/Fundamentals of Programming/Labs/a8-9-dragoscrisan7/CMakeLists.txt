cmake_minimum_required(VERSION 3.21)
project(a8_9_dragoscrisan7)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(a8_9_dragoscrisan7
        Dog.cpp
        Dog.h
        Repository.cpp
        Repository.h
        UserRepository.cpp
        UserRepository.h
        Service.cpp
        Service.h
        UserService.cpp
        UserService.h
        Ui.cpp
        Ui.h
        main.cpp
        Validators.h
        Validators.cpp
        CSVfile.h
        CSVfile.cpp
        HTMLfile.h
        HTMLfile.cpp)
