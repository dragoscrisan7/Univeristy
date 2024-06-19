//
// Created by Dragos on 1/8/2024.
//

#ifndef SERVERHOMEWORK_ASYNCAWAITSOLUTION_H
#define SERVERHOMEWORK_ASYNCAWAITSOLUTION_H

#include <iostream>
#include <vector>
#include <future>
#include <coroutine>
#include "Parser.h"

class AsyncAwaitSolution : public Common {
public:
    AsyncAwaitSolution(const std::vector<std::string>& urls) : Common(urls) {}

    void Run() override {
        ForEach([this](int index, const std::string& url) {
            // Use std::async to run tasks asynchronously
            std::async(std::launch::async, [this, index, url]() {
                // Start a new SocketHandler for each URL
                SocketHandler socket(url, index);

                // Connect asynchronously
                ConnectAsync(socket).get();

                // Send asynchronously
                SendAsync(socket).get();

                // Receive asynchronously
                ReceiveAsync(socket).get();

                // Shutdown and close the socket
                socket.ShutdownAndClose();
            });
        });
    }

    std::string ParserType() override {
        return "AsyncAwait";
    }

private:
    std::future<void> ConnectAsync(SocketHandler& socket) {
        return std::async(std::launch::async, [this, &socket]() {
            socket.BeginConnect([this](SocketHandler& connectedSocket) {
                // Log connected event
                LogConnected(connectedSocket);
            });
        });
    }

    std::future<void> SendAsync(SocketHandler& socket) {
        return std::async(std::launch::async, [this, &socket]() {
            socket.BeginSend([this](SocketHandler& sentSocket, int numberOfSentBytes) {
                // Log sent event
                LogSent(sentSocket, numberOfSentBytes);
            });
        });
    }

    std::future<void> ReceiveAsync(SocketHandler& socket) {
        return std::async(std::launch::async, [this, &socket]() {
            socket.BeginReceive([this](SocketHandler& receivedSocket) {
                // Log received event
                LogReceived(receivedSocket);
            });
        });
    }
};

#endif //SERVERHOMEWORK_ASYNCAWAITSOLUTION_H
