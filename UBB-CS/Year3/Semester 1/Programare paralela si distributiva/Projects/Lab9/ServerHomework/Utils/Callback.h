//
// Created by Dragos on 10/29/2023.
//

#ifndef SERVERHOMEWORK_CALLBACK_H
#define SERVERHOMEWORK_CALLBACK_H


#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include "../SocketHandler/SocketHandler.h" // Include your SocketHandler class header
#include "Parser.h"

class CallbackSolution : public Common {
public:
    CallbackSolution(const std::vector<std::string>& urls) : Common(urls) {}

    void Run() override {
        ForEach([this](int index, const std::string& url) {
            Start(SocketHandler(url, index));
        });
    }

    std::string ParserType() override {
        return "Callback";
    }

private:
    void Start(SocketHandler socket) {
        socket.BeginConnect([this](SocketHandler& socket) {
            LogConnected(socket);
            socket.BeginSend([this](SocketHandler& socket, int numberOfSentBytes) {
                LogSent(socket, numberOfSentBytes);
                socket.BeginReceive([this](SocketHandler& socket) {
                    LogReceived(socket);
                    socket.ShutdownAndClose();
                });
            });
        });
    }
};

#endif //SERVERHOMEWORK_CALLBACK_H