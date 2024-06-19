cmake_minimum_required(VERSION 3.21)
project(a3_4_dragoscrisan7 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(a3_4_dragoscrisan7
        Bakery.c
        Bakery.h
        Bakery_repository.c
        Bakery_Repository.h
        Dynamic_array.c
        Dynamic_array.h
        main.c
        Services.c
        Services.h
        Operation.c
        Operation.h
        UI.c
        UI.h
        Test.c
        Test.h
        )
