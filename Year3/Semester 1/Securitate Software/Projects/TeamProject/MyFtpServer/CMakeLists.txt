cmake_minimum_required(VERSION 3.21)
project(MyFtpServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyFtpServer main.cpp)


target_link_libraries(MyFtpServer ws2_32)
