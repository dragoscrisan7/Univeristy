// HttpSocketHandler.h
#ifndef HTTP_SOCKET_HANDLER_H
#define HTTP_SOCKET_HANDLER_H

#include <string>
#include <functional>

class HttpSocketHandler {
public:
    HttpSocketHandler(const std::string& url, int id);

    void BeginConnect(std::function<void(HttpSocketHandler&)> connectedCallback);
    void BeginSend(std::function<void(HttpSocketHandler&, int)> sentCallback);
    void BeginReceive(std::function<void(HttpSocketHandler&)> receivedCallback);

    void ShutdownAndClose();

    const std::string& GetResponseContent() const;

private:
    void HandleConnected();
    void HandleSent(int numberOfSentBytes);
    void HandleReceived();

    std::string baseUrl_;
    std::string urlPath_;
    int id_;
    std::string responseContent_;

    std::function<void(HttpSocketHandler&)> connectedCallback_;
    std::function<void(HttpSocketHandler&, int)> sentCallback_;
    std::function<void(HttpSocketHandler&)> receivedCallback_;
};

#endif // HTTP_SOCKET_HANDLER_H
