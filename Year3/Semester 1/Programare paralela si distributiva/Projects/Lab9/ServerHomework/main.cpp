#include <iostream>
#include "Utils/Callback.h"

int main() {

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup failed");
        return 1; // Return a non-zero value to indicate an error
    }
    std::vector<std::string> urls = { "www.apache.org/", "github.github.io/", "www.wikipedia.org/" };

    CallbackSolution parser(urls);
    parser.Run();

    WSACleanup();

    return 0;
}
