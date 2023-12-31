//
// Created by Dragos on 10/30/2023.
//

#ifndef SERVERHOMEWORK_TASKSOLUTION_H
#define SERVERHOMEWORK_TASKSOLUTION_H

#include "Parser.h"  // Include the C++ Common class
#include <vector>
#include <string>
#include <future>

//class TaskSolution : public Common {
//public:
//    TaskSolution(const std::vector<std::string>& urls) : Common(urls) {}
//
//protected:
//    std::string ParserType() override {
//        return "Task";
//    }
//
//    void Run() override {
//        std::vector<std::future<void>> tasks;
//        for (int i = 0; i < urls.size(); i++) {
//            const std::string& url = urls[i];
//            tasks.push_back(std::async(std::launch::async, [this, url, i]() {
//                Start(SocketHandler::Create(url, i));
//            }));
//        }
//
//        for (auto& task : tasks) {
//            task.get();
//        }
//    }
//
//
//private:
//    void Start(SocketHandler& socket) {
//        socket.BeginConnectAsync().get();
//        LogConnected(socket);
//
//        auto sendTask = socket.BeginSendAsync();
//        sendTask.get();
//        int numberOfSentBytes = sendTask.get();
//        LogSent(socket, numberOfSentBytes);
//
//        socket.BeginReceiveAsync().get();
//        LogReceived(socket);
//
//        socket.ShutdownAndClose();
//    }
//};
//
class TaskSolution : public Common {
public:
    TaskSolution(const std::vector<std::string>& urls) : Common(urls) {}

    void Run() override {
        ForEach([this](int index, const std::string& url) {
            // Use std::async to run tasks asynchronously
            std::future<void> task = std::async(std::launch::async, [this, index, url]() {
                // Start a new SocketHandler for each URL
                SocketHandler socket(url, index);

                // Connect asynchronously
                std::future<void> connectTask = std::async(std::launch::async, [this, &socket]() {
                    socket.BeginConnect([this](SocketHandler& connectedSocket) {
                        // Log connected event
                        LogConnected(connectedSocket);
                    });
                });

                connectTask.get();

                // Send asynchronously
                std::future<void> sendTask = std::async(std::launch::async, [this, &socket]() {
                    socket.BeginSend([this](SocketHandler& sentSocket, int numberOfSentBytes) {
                        // Log sent event
                        LogSent(sentSocket, numberOfSentBytes);
                    });
                });

                // Wait for the send task to finish before proceeding
                sendTask.get();

                // Receive asynchronously
                std::future<void> receiveTask = std::async(std::launch::async, [this, &socket]() {
                    socket.BeginReceive([this](SocketHandler& receivedSocket) {
                        // Log received event
                        LogReceived(receivedSocket);
                        // Shutdown and close the socket
                        receivedSocket.ShutdownAndClose();
                    });
                });

                // Wait for the receive task to finish before proceeding
                receiveTask.get();
            });
        });
    }

    std::string ParserType() override {
        return "Task";
    }
};


#endif //SERVERHOMEWORK_TASKSOLUTION_H