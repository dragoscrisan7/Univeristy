cmake_minimum_required(VERSION 3.21)
project(Lab6)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab6 main.cpp
        multiThreads/MultiThreads.cpp
        multiThreads/MultiThreads.h
        threadsPool/ThreadPool.cpp
        threadsPool/ThreadPool.h
        utils/Utils.cpp
        utils/Utils.h)
