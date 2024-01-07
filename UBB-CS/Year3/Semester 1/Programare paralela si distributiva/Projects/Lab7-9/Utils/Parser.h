//
// Created by Dragos on 10/29/2023.
//

#ifndef SERVERHOMEWORK_PARSER_H
#define SERVERHOMEWORK_PARSER_H

#include <iostream>
#include <vector>
#include <functional>
#include "../SocketHandler/SocketHandler.h"  // Include the C++ SocketHandler class

class Common {
private:
    std::vector<std::string> Urls;

protected:
    virtual std::string ParserType() = 0;

public:
    Common(const std::vector<std::string>& urls) : Urls(urls) {
        Run();
    }

    void ForEach(const std::function<void(int, const std::string&)>& action) {
        int count = 0;
        for (const std::string& url : Urls) {
            action(count++, url);
        }
    }

    template <typename T>
    std::vector<T> Map(const std::function<T(int, const std::string&)>& mapper) {
        std::vector<T> result;
        int count = 0;
        for (const std::string& url : Urls) {
            result.push_back(mapper(count++, url));
        }
        return result;
    }

    void LogConnected(SocketHandler& socket) {
        std::cout << ParserType() << "-" << socket.Id << ": Socket connected to " << socket.BaseUrl << " (" << socket.UrlPath << ")" << std::endl;
    }

    void LogSent(SocketHandler& socket, int numberOfSentBytes) {
        std::cout << ParserType() << "-" << socket.Id << ": Sent " << numberOfSentBytes << " bytes to server." << std::endl;
    }

    void LogReceived(SocketHandler& socket) {
        //std::cout << socket.GetResponseContent() << std::endl;
        std::cout << "Header Length: " << socket.GetResponseContent().length() << std::endl;
        std::cout << "Header Text:\n" << socket.GetResponseContent() << std::endl;
    }

    virtual void Run() {}
};


#endif //SERVERHOMEWORK_PARSER_H
