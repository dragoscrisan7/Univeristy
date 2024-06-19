cmake_minimum_required(VERSION 3.21)
project(PregatireDragos2)

set(CMAKE_CXX_STANDARD 14)

add_executable(PregatireDragos2 main.cpp
        Appliance.cpp
        Appliance.h
        DishWasher.cpp
        DishWasher.h
        Refrigerator.cpp
        Refrigerator.h
        Service.cpp
        Service.h
        ui.cpp
        ui.h)
