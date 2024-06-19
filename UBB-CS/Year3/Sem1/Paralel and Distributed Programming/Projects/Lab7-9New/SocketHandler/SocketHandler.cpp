//
// Created by Dragos on 1/5/2024.
//
#include "SocketHandler.h"
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

SocketHandler::SocketHandler() : socketHandle(INVALID_SOCKET), contentLength(0) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
    }
}

bool SocketHandler::connectToServer(const std::string& host) {
    struct sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;

    cleanedHost = host;
    size_t pos = cleanedHost.find("https://");
    if (pos != std::string::npos) {
        cleanedHost = cleanedHost.substr(pos + 8); // Remove "https://"
    }

    // Use 443 for https, 80 for http
    int port = (cleanedHost.find("https://") == 0) ? 443 : 80;
    serverAddr.sin_port = htons(port);
    cleanedHost = (cleanedHost.back() == '/') ? cleanedHost.substr(0, cleanedHost.size() - 1) : cleanedHost;

    // Try to convert to an IP address
    serverAddr.sin_addr.s_addr = inet_addr(cleanedHost.c_str());
    if (serverAddr.sin_addr.s_addr == INADDR_NONE) {
        // The host is a domain name
        hostent* hostInfo = gethostbyname(cleanedHost.c_str());

        if (hostInfo == nullptr) {
            std::cerr << "Failed to resolve host: " << host << std::endl;
            return false;
        }

        memcpy(&serverAddr.sin_addr, hostInfo->h_addr, hostInfo->h_length);
    }

    socketHandle = socket(AF_INET, SOCK_STREAM, 0);
    if (socketHandle == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        return false;
    }

    if (connect(socketHandle, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed" << std::endl;
        closesocket(socketHandle);
        return false;
    }

    return true;
}

bool SocketHandler::sendHttpRequest(const std::string& resource) {
    std::string request = "GET " + resource + " HTTP/1.1\r\n"
                                              "Host: " + cleanedHost + "\r\n"
                                                                       "Connection: close\r\n\r\n";

    if (send(socketHandle, request.c_str(), static_cast<int>(request.size()), 0) == SOCKET_ERROR) {
        std::cerr << "Failed to send HTTP request" << std::endl;
        return false;
    }

    return true;
}


bool SocketHandler::receiveHttpHeader() {
    const int bufferSize = 1024;
    char buffer[bufferSize];

    int bytesRead;

    do {
        bytesRead = recv(socketHandle, buffer, bufferSize - 1, 0);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            httpHeader += buffer;
        }
        else if (bytesRead == 0) {
            std::cerr << "Connection closed by remote host" << std::endl;
            return false;
        }
        else {
            std::cerr << "Error receiving data" << std::endl;
            return false;
        }

        // Check for the end of the header ("\r\n\r\n")
        size_t found = httpHeader.find("\r\n\r\n");
        if (found != std::string::npos) {
            break;
        }
    } while (true);

    std::cout << "Received HTTP Header:\n" << httpHeader << std::endl;

    // Check for redirection
    if (isRedirection()) {
        handleRedirection();
        return receiveHttpHeader();  // Send another request after redirection
    }

    // Parse Content-Length from the header
    parseContentLength();

    return true;
}

bool SocketHandler::isRedirection() const {
    return httpHeader.find("301 Moved Permanently") != std::string::npos;
}

void SocketHandler::handleRedirection() {
    // Extract the new location from the Location header
    size_t locationPos = httpHeader.find("Location:");
    if (locationPos != std::string::npos) {
        size_t endPos = httpHeader.find("\r\n", locationPos);
        if (endPos != std::string::npos) {
            std::string newLocation = httpHeader.substr(locationPos + 10, endPos - (locationPos + 10));
            std::cout << "Redirecting to: " << newLocation << std::endl;
            // Implement your logic to follow the redirection
            // For simplicity, just print the new location here
        }
    }
}

void SocketHandler::parseContentLength() {
    const std::string contentLengthTag = "Content-Length:";
    size_t pos = httpHeader.find(contentLengthTag);
    if (pos != std::string::npos) {
        size_t endPos = httpHeader.find("\r\n", pos);
        if (endPos != std::string::npos) {
            std::string lengthStr = httpHeader.substr(pos + contentLengthTag.length(), endPos - (pos + contentLengthTag.length()));
            contentLength = std::stoi(lengthStr);
            std::cout << "Content Length: " << contentLength << std::endl;
        }
    }
}

int SocketHandler::getContentLength() const {
    return contentLength;
}

bool SocketHandler::receiveContent() {
    const int bufferSize = 1024;
    char buffer[bufferSize];
    int bytesToReceive = contentLength;

    while (bytesToReceive > 0) {
        int bytesRead = recv(socketHandle, buffer, std::min(bufferSize, bytesToReceive), 0);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            std::cout << buffer;
            bytesToReceive -= bytesRead;
        }
        else if (bytesRead == 0) {
            std::cerr << "Connection closed by remote host" << std::endl;
            return false;
        }
        else {
            std::cerr << "Error receiving data" << std::endl;
            return false;
        }
    }

    return true;
}

void SocketHandler::closeSocket() {
    if (socketHandle != INVALID_SOCKET) {
        closesocket(socketHandle);
    }
    WSACleanup();
}

const std::string& SocketHandler::getHttpHeader() const {
    return httpHeader;
}