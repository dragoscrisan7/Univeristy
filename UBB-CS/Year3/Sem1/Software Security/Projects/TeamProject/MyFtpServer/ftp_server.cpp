#include <stdexcept>
#include <iostream>
#include <thread>
#include "ftp_server.h"

FtpServer::FtpServer(int port) :
        controlConnection(std::to_string(port))
{
    controlConnection.startListening();
}

inline string FtpServer::message()
{
    return this->lastMessage;
}
