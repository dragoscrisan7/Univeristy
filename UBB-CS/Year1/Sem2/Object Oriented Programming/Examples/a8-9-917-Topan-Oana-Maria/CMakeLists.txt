cmake_minimum_required(VERSION 3.21)
project(a8_9_917_Topan_Oana_Maria)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(a8_9_917_Topan_Oana_Maria
        repository/DynamicVector.cpp
        repository/DynamicVector.h
        domain/Recipe.cpp
        domain/Recipe.h
        repository/Repository.cpp
        repository/Repository.h
        repository/Watch_list.cpp
        repository/Watch_list.h
        service/Service.cpp
        service/Service.h
        user_interface/User_interface.cpp
        user_interface/User_interface.h
        main.cpp
        domain/Duration.h
        domain/Duration.cpp
        tests/Tests.cpp
        tests/Tests.h
        validation/validator.h
        validation/validator.cpp
        repository/Watch_list_csv.h
        repository/Watch_list_csv.cpp
        repository/Watch_list_html.h
        repository/Watch_list_html.cpp
        lab_activity/Comparator.h
        lab_activity/Comparator.cpp
        lab_activity/Comparator_descending_by_title.h
        lab_activity/Comparator_descending_by_title.cpp
        lab_activity/Comparator_ascending_by_likes.h
        lab_activity/Comparator_ascending_by_likes.cpp)
