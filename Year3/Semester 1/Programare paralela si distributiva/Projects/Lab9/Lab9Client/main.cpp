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
    addrinfo hints{};
    hints.ai_family = AF_INET;
    addrinfo* result;
    int res = getaddrinfo(srvName.c_str(), nullptr, &hints, &result);
    if (res != 0) {
        std::cerr << "Failed to get server address: " << gai_strerror(res) << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in srvAddr = *reinterpret_cast<sockaddr_in*>(result->ai_addr);
    freeaddrinfo(result);

    std::cout << "IP=" << inet_ntoa(srvAddr.sin_addr) << std::endl;

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

    srvAddr.sin_port = htons(srvPort);

    if (connect(conn, reinterpret_cast<sockaddr*>(&srvAddr), sizeof(srvAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to the server." << std::endl;
        closesocket(conn);
        WSACleanup();
        return 1;
    }

    while (true) {
        std::cout << "Give 2 numbers, enter 0 for ending." << std::endl;
        std::cout << "A=";
        std::string strA;
        std::cin >> strA;
        if (strA == "0") {
            break;
        }
        std::cout << "B=";
        std::string strB;
        std::cin >> strB;

        std::string toSendStr = strA + " " + strB + "\n";
        send(conn, toSendStr.c_str(), static_cast<int>(toSendStr.size()), 0);

        char recvBuffer[2048];
        int retBytes = recv(conn, recvBuffer, sizeof(recvBuffer), 0);
        if (retBytes <= 0) {
            std::cerr << "Failed to receive data from the server." << std::endl;
            break;
        }
        std::string retString(recvBuffer, retBytes);
        std::cout << "Received: " << retString << std::endl;
    }

    closesocket(conn);
    WSACleanup();

    return 0;
}
