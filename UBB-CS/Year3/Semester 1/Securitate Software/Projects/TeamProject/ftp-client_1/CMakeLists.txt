cmake_minimum_required(VERSION 3.27)
project(ftp_client)

set(CMAKE_CXX_STANDARD 17)

include_directories(ftp-client)

add_executable(ftp_client
        ftp-client/main.cpp
        ftp-client/FtpClient.cpp
        ftp-client/FtpClient.h
        ftp-client/TcpConnection.cpp
        ftp-client/TcpConnection.h)

target_link_libraries(ftp_client PRIVATE ws2_32.lib)