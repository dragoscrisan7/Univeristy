#include <iostream>
#include <vector>
#include "SocketHandler/SocketHandler.h"

int main() {
    const std::string host = "www.wikipedia.org";
    const std::string resource = "/index.html";

    SocketHandler socketHandler;

    if (socketHandler.connectToServer(host) && socketHandler.sendHttpRequest(resource)) {
        if (socketHandler.receiveHttpHeader()) {
            socketHandler.receiveContent();
        }
    }

    socketHandler.closeSocket();

    return 0;
}
