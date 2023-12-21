cmake_minimum_required(VERSION 3.21)
project(Lab9Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab9Server main.cpp)

# Link the Winsock libraries (Windows-specific)
if(WIN32)
    target_link_libraries(Lab9Server wsock32 ws2_32)
endif()