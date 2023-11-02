//
// Created by Dragos on 10/28/2023.
//

#ifndef SERVERHOMEWORK_SESSION_H
#define SERVERHOMEWORK_SESSION_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include "../Parser/Parser.h"
#include <thread>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

class Session {
public:
    Session(SOCKET conn) : _conn(conn), _bufferSize(1024), _buffer(new char[_bufferSize]), _bufferPos(0), _httpData("") {}

    void Start() {
        OnBytesReceived(0);
    }

    void HandleHttpResponse(const std::string& httpResponse) {
        HttpHeaderParser parser(httpResponse);
        int contentLength = parser.getContentLength();

        // Handle the content here if needed
        // ...

        closesocket(_conn);
    }

private:
    void OnBytesReceived(int bytesRead) {
        if (bytesRead <= 0) {
            std::cout << "Connection closed" << std::endl;
            closesocket(_conn);
            delete[] _buffer;
            return;
        }

        _bufferPos += bytesRead;
        _httpData += std::string(_buffer, bytesRead);

        // Check if we've received the complete HTTP response
        if (IsHttpResponseComplete()) {
            HandleHttpResponse(_httpData);
            _httpData.clear();
            _bufferPos = 0;
        } else {
            // Continue to receive data
            OnBytesReceived(0);
        }
    }

    bool IsHttpResponseComplete() {
        // Implement logic to check if a complete HTTP response has been received
        // For example, look for double CRLF ("\r\n\r\n") as the separator between headers and body.
        size_t found = _httpData.find("\r\n\r\n");
        return (found != std::string::npos);
    }

    // Other private members...

    SOCKET _conn;
    int _bufferSize;
    char* _buffer;
    int _bufferPos;
    std::string _httpData;
};
#endif //SERVERHOMEWORK_SESSION_H
