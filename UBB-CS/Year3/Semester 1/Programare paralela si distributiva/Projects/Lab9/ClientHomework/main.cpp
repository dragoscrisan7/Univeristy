#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    std::cout << "Server Name/IP=";
    std::string srvName;
    std::cin >> srvName;

    std::cout << "Server port=";
    std::string srvPortStr;
    std::cin >> srvPortStr;
    int srvPort = std::stoi(srvPortStr);

    SOCKET conn = socket(AF_INET, SOCK_STREAM, 0);
    if (conn == INVALID_SOCKET) {
        std::cerr << "Failed to create a socket." << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in srvAddr{};
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(srvPort);

    // Use getaddrinfo to resolve the server address
    addrinfo hints{};
    hints.ai_family = AF_INET;
    addrinfo* result;
    int res = getaddrinfo(srvName.c_str(), srvPortStr.c_str(), &hints, &result);
    if (res != 0) {
        std::cerr << "Failed to get server address: " << gai_strerror(res) << std::endl;
        closesocket(conn);
        WSACleanup();
        return 1;
    }

    srvAddr = *reinterpret_cast<sockaddr_in*>(result->ai_addr);
    freeaddrinfo(result);

    if (connect(conn, reinterpret_cast<sockaddr*>(&srvAddr), sizeof(srvAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to the server." << std::endl;
        closesocket(conn);
        WSACleanup();
        return 1;
    }

    // Construct an HTTP GET request
    std::string getRequest = "GET / HTTP/1.1\r\nHost: " + srvName + "\r\n\r\n";

    send(conn, getRequest.c_str(), static_cast<int>(getRequest.size()), 0);

    char recvBuffer[2048];
    int retBytes = recv(conn, recvBuffer, sizeof(recvBuffer), 0);
    if (retBytes <= 0) {
        std::cerr << "Failed to receive data from the server." << std::endl;
    } else {
        std::string retString(recvBuffer, retBytes);
        std::cout << "Received:\n" << retString << std::endl;
    }

    closesocket(conn);
    WSACleanup();

    return 0;
}
