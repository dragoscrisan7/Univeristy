cmake_minimum_required(VERSION 3.21)
project(graph_lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(graph_lab1 main.cpp
        Graph.cpp
        Graph.h
        Test.cpp
        Test.h)
