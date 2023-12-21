//
// Created by Dragos on 10/30/2023.
//

#ifndef SERVERHOMEWORK_TASKSOLUTION_H
#define SERVERHOMEWORK_TASKSOLUTION_H

#include "Parser.h"  // Include the C++ Common class
#include "../SocketHandler/SocketHandler.h"  // Include the C++ SocketHandler class
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
#endif //SERVERHOMEWORK_TASKSOLUTION_H