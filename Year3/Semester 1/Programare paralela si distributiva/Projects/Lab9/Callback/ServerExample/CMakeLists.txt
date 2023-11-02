cmake_minimum_required(VERSION 3.21)
project(Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Server main.cpp)

# Link the Winsock libraries (Windows-specific)
if(WIN32)
    target_link_libraries(Server wsock32 ws2_32)
endif()