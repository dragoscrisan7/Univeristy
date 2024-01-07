cmake_minimum_required(VERSION 3.27)
project(Lab7_9New)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab7_9New main.cpp
        SocketHandler/SocketHandler.h
        SocketHandler/SocketHandler.h
        SocketHandler/SocketHandler.cpp)

if(WIN32)
    target_link_libraries(Lab7_9New wsock32 ws2_32)
endif()