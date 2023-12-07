#include "ftp_server.h"

#include <ws2tcpip.h>

FtpServer::FtpServer(std::string port)
{
    int r;

    // WSAStartup
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        throw FtpException("WSAStartup failed.");

    // Setup listener
    setupListener(port);
}

FtpServer::~FtpServer()
{
    closesocket(serverSocket);
    WSACleanup();
}

void FtpServer::start()
{
    while (true)
    {
        // Accept incoming connection
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET)
        {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }

        // Create a thread to handle the client
        CreateThread(NULL, 0, clientThread, (LPVOID)clientSocket, 0, NULL);
    }
}

void FtpServer::setupListener(std::string port)
{
    int r;

    // Resolve the server address and port
    addrinfo hints, *result = NULL;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    if ((r = getaddrinfo(NULL, port.c_str(), &hints, &result)) != 0)
        throw FtpException((std::string("getaddrinfo failed: ") + std::to_string(r)).c_str());

    // Create a socket for the server
    serverSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (serverSocket == INVALID_SOCKET)
    {
        freeaddrinfo(result);
        throw FtpException("Error at socket.");
    }

    // Bind the socket
    if (bind(serverSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
    {
        freeaddrinfo(result);
        closesocket(serverSocket);
        throw FtpException("Bind failed.");
    }

    freeaddrinfo(result);

    // Listen on the socket
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        closesocket(serverSocket);
        throw FtpException("Listen failed.");
    }
}

DWORD WINAPI FtpServer::clientThread(LPVOID lpParam)
{
SOCKET clientSocket = (SOCKET)lpParam;

FtpServer ftpServer;
ftpServer.processClient(clientSocket);

closesocket(clientSocket);
return 0;
}

void FtpServer::processClient(SOCKET clientSocket)
{
    TcpConnection clientConnection(clientSocket);

    // Implement FTP command handling here
    // Example: clientConnection.put("220 Welcome to FTP Server\r\n");

    // Sample: send a welcome message
    sendResponse(clientSocket, "220 Welcome to FTP Server\r\n");

    // You need to implement the logic to handle FTP commands and respond accordingly
    // For example, LIST, RETR, STOR, etc.

    // You can refer to the FTP RFC (https://www.ietf.org/rfc/rfc959.txt) for details on FTP commands and responses.
}

void FtpServer::sendResponse(SOCKET clientSocket, const std::string& response)
{
    if (send(clientSocket, response.c_str(), response.length(), 0) == SOCKET_ERROR)
        std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
}

FtpException::FtpException(const char* message) : std::exception(message) {}
