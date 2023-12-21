cmake_minimum_required(VERSION 3.21)
project(MyFtpServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyFtpServer main.cpp
        ftp_server.cpp
        TcpConnection.cpp
        TcpConnection.h
        ftp_server.h)


target_link_libraries(MyFtpServer ws2_32)

target_compile_features(MyFtpServer PRIVATE cxx_std_17)
