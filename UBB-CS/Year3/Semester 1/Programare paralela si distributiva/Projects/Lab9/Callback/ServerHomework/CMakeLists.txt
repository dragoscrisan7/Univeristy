cmake_minimum_required(VERSION 3.21)
project(ServerHomework)

set(CMAKE_CXX_STANDARD 14)

add_executable(ServerHomework main.cpp
        Parser/Parser.cpp
        Parser/Parser.h
        Session/Session.cpp
        Session/Session.h
        Socket/HttpSocketHandler.cpp
        Socket/HttpSocketHandler.h)

# Link the Winsock libraries (Windows-specific)
if(WIN32)
    target_link_libraries(ServerHomework wsock32 ws2_32)
endif()