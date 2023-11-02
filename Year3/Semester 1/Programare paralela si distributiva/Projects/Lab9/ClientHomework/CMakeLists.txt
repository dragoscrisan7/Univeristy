cmake_minimum_required(VERSION 3.21)
project(ClientHomework)

set(CMAKE_CXX_STANDARD 14)

add_executable(ClientHomework main.cpp)

# Link the Winsock libraries (Windows-specific)
if(WIN32)
    target_link_libraries(ClientHomework wsock32 ws2_32)
endif()