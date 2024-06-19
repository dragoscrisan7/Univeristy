//
// Created by Dragos on 12/7/2023.
//

#ifndef MYFTPSERVER_FTP_SERVER_H
#define MYFTPSERVER_FTP_SERVER_H

#pragma once

#include <winsock2.h>
#include "TcpConnection.h"

class FtpServer {
private:
    TcpConnection controlConnection;
    string lastMessage;
public:

    FtpServer(int port);

    inline string message();

};



#endif //MYFTPSERVER_FTP_SERVER_H
