//
// Created by Dragos on 1/5/2024.
//

#ifndef LAB7_9NEW_SOCKETHANDLER_H
#define LAB7_9NEW_SOCKETHANDLER_H

#include <string>

class SocketHandler {
public:
    SocketHandler();

    const std::string& getHttpHeader() const;
    // Connect to the specified host and port
    bool connectToServer(const std::string& host);

    // Send an HTTP GET request for the specified resource
    bool sendHttpRequest(const std::string& resource);

    // Receive and print the HTTP header information
    bool receiveHttpHeader();

    void parseContentLength();

    // Get the content length from the HTTP header
    int getContentLength() const;

    // Receive and print the content based on the content length
    bool receiveContent();

    // Clean up and close the socket
    void closeSocket();

private:
    int socketHandle;
    int contentLength;
    static const int DefaultHttpPort = 80;
    static const int BufferSize = 1024;
    std::string cleanedHost;
    std::string httpHeader;

    bool isRedirection() const;
    void handleRedirection();
};

#endif //LAB7_9NEW_SOCKETHANDLER_H
