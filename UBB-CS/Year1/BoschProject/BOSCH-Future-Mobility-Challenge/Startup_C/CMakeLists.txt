# INCLUDE(CMakeForceCompiler)
cmake_minimum_required(VERSION 2.8.11)
project(bosch_adc_lab)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

#find_package(Boost REQUIRED COMPONENTS system thread)

FIND_PACKAGE(Boost)
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Users/Vlad/OneDrive/Facultate/Fundamentals of Programing/GitHub/boost_1_78_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Users/Vlad/OneDrive/Facultate/Fundamentals of Programing/GitHub/boost_1_78_0/libs")
include_directories(include)
file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp")

add_executable(app1 app1.cpp ${SOURCES})

target_link_libraries (app1 ${Boost_LIBRARIES} -lpthread -lm)
