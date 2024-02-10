#ifndef SERVERHOMEWORK_SOCKETHANDLER_H
#define SERVERHOMEWORK_SOCKETHANDLER_H

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <functional>
#include <winsock.h>
#include <future>

class SocketHandler {
public:
    int Id;
    std::string BaseUrl;
    std::string UrlPath;

    SocketHandler(const std::string& url, int id) : Id(id) {
        size_t index = url.find('/');
        BaseUrl = (index != std::string::npos) ? url.substr(0, index) : url;
        UrlPath = (index != std::string::npos) ? url.substr(index) : "/";
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed" << std::endl;
        }
    }

    void BeginConnect(const std::function<void(SocketHandler&)>& onConnected) {
        sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(DefaultHttpPort);

        hostent* server = gethostbyname(BaseUrl.c_str());
        if (server == nullptr) {
            perror("Error in gethostbyname");
            return;
        }
        memcpy(&serverAddress.sin_addr, server->h_addr, server->h_length);

        socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (connect(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
            int error = WSAGetLastError();
            std::cerr << "Error in connect: " << error << std::endl;
            return;
        }

        onConnected(*this);
    }

    void BeginSend(const std::function<void(SocketHandler&, int)>& onSent) {
        std::string stringToSend = "GET " + UrlPath + " HTTP/1.1\r\n";
        stringToSend += "Host: " + BaseUrl + "\r\n";
        stringToSend += "Content-Length: 0\r\n\r\n";

        const char* encodedString = stringToSend.c_str();
        int encodedStringLength = stringToSend.length();

        int numberOfSentBytes = send(socketDescriptor, encodedString, encodedStringLength, 0);
        if (numberOfSentBytes < 0) {
            perror("Error in send");
            return;
        }

        onSent(*this, numberOfSentBytes);
    }

    void BeginReceive(const std::function<void(SocketHandler&)>& onReceived) {
        char buffer[BufferSize];
        ResponseContent.clear();

        ssize_t numberOfReadBytes = recv(socketDescriptor, buffer, BufferSize, 0);

        // Check for HTTP header
        size_t headerEnd = ResponseContent.find("\r\n\r\n");
        if (headerEnd != std::string::npos) {
            std::string header = ResponseContent.substr(0, headerEnd + 4);
            std::cout << "Header Length: " << header.length() << std::endl;
            std::cout << "Header Text:\n" << header << std::endl;

            // Check if it's a redirect (HTTP status code 301)
            if (header.find("HTTP/1.1 301") != std::string::npos) {
                size_t locationStart = header.find("Location: ");
                if (locationStart != std::string::npos) {
                    size_t locationEnd = header.find("\r\n", locationStart);
                    if (locationEnd != std::string::npos) {
                        std::string newLocation = header.substr(locationStart + 10, locationEnd - (locationStart + 10));
                        std::cout << "Redirecting to: " << newLocation << std::endl;

                        // Close the current connection and initiate a new connection to the new location
                        ShutdownAndClose();
                        SocketHandler newSocket(newLocation, Id);
                        newSocket.BeginConnect(onReceived);
                        return;
                    }
                }
            }
        }

        while (numberOfReadBytes > 0) {
            ResponseContent.append(buffer, numberOfReadBytes);
            numberOfReadBytes = recv(socketDescriptor, buffer, BufferSize, 0);
        }

        if (numberOfReadBytes < 0) {
            perror("Error in recv");
            return;
        }

        onReceived(*this);
    }

    void ShutdownAndClose() {
        shutdown(socketDescriptor, 1);
        close(socketDescriptor);
    }

    std::string GetResponseContent() {
        return ResponseContent;
    }

private:
    static const int DefaultHttpPort = 80;
    static const int BufferSize = 1024;
    int socketDescriptor;
    std::string ResponseContent;
};

#endif //SERVERHOMEWORK_SOCKETHANDLER_H