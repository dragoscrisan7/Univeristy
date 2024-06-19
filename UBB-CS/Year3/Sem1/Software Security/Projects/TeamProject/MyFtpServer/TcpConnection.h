#pragma once

#include <winsock2.h>
#include <string>
#include <mutex>

using std::string;

#define MAX_CONTROL_SIZE 1024

class TcpConnection
{
private:
	WSADATA wsaData;
    SOCKET serverSocket;

    std::mutex loginMutex;
    bool isLoggedIn;
    string loggedInUsername;
    string selectedTransferType;
public:
	TcpConnection(string port);
	~TcpConnection();

    void startListening();
    void handleClient(SOCKET clientSocket);

    bool login(string username, string password);

    SOCKET openDataSocket(int port);
    void sendPortCommand(int dataPort, SOCKET clientSocket);
    void handleListCommand(SOCKET dataSocket, const string& dir);
    std::string getDirectoryListing(const std::string& dir);
    void handleUploadCommand(SOCKET dataSocket, const std::string& filePath, SOCKET clientSocket);
    void handleDownloadCommand(SOCKET dataSocket, const std::string& filePath, SOCKET clientSocket);

    std::string get(int maxLength, SOCKET dataSocket) const;
};

class TcpException : public std::exception {
public:
    TcpException(const char* message);
    const char* what() const noexcept override;

private:
    std::string errorMessage;
};