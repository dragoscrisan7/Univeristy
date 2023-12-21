/*FTP server*/
#include <winsock2.h>
#include <windows.h>

#include <stdlib.h>
#include <string>

/*for getting file size using stat()*/
#include<sys/stat.h>

/*for O_RDONLY*/
#include<fcntl.h>
#include <iostream>
#include "ftp_server.h"

#pragma comment(lib, "ws2_32.lib")

int main() {
    try {
        FtpServer ftpServer(12345);

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}