//
// Created by Dragos on 12/7/2023.
//

#ifndef MYFTPSERVER_FTP_SERVER_H
#define MYFTPSERVER_FTP_SERVER_H

#pragma once

#include <winsock2.h>
#include <string>
#include <iostream>

class FtpServer
{
private:
    WSADATA wsaData;
    SOCKET serverSocket;

public:
    FtpServer(std::string port);
    ~FtpServer();

    void start();

private:
    void setupListener(std::string port);
    void handleClient(SOCKET clientSocket);

    static DWORD WINAPI clientThread(LPVOID lpParam);
    void processClient(SOCKET clientSocket);
    void sendResponse(SOCKET clientSocket, const std::string& response);
};

class FtpException : public std::exception
{
public:
    FtpException(const char* message);
};


#endif //MYFTPSERVER_FTP_SERVER_H
