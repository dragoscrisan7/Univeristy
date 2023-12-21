cmake_minimum_required(VERSION 3.21)
project(ServerHomework)

set(CMAKE_CXX_STANDARD 14)

add_executable(ServerHomework main.cpp
        Utils/Parser.h
        Utils/Parser.cpp
        SocketHandler/SocketHandler.h
        SocketHandler/SocketHandler.cpp
        Utils/Callback.h
        Utils/Callback.cpp
        Utils/TaskSolution.h
        Utils/TaskSolution.cpp
        )


# Link the Winsock libraries (Windows-specific)
if(WIN32)
    target_link_libraries(ServerHomework wsock32 ws2_32)
endif()