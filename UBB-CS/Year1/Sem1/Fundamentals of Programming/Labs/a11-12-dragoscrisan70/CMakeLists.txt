cmake_minimum_required(VERSION 3.21)
project(a11_12_dragoscrisan7)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(a11_12_dragoscrisan7
        CSVfile.cpp
        CSVfile.h
        Dog.cpp
        Dog.h
        HTMLfile.cpp
        HTMLfile.h
        main.cpp
        Repository.cpp
        Repository.h
        Service.cpp
        Service.h
        Ui.cpp
        Ui.h
        UserRepository.cpp
        UserRepository.h
        UserService.cpp
        UserService.h
        Validators.cpp
        Validators.h)
