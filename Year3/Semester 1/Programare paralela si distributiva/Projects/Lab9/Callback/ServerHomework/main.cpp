#include "Session/Session.h"  // Include the HTTP header parser class you created

#pragma comment(lib, "ws2_32.lib")

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main(int argc, char* argv[]) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        WSACleanup();
        return 1;
    }

    int port;
    try {
        port = std::stoi(argv[1]);
    } catch (const std::exception& e) {
        std::cerr << "Invalid port number: " << e.what() << std::endl;
        WSACleanup();
        return 1;
    }

    SOCKET listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listeningSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create a socket." << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in listeningEndpoint;
    listeningEndpoint.sin_family = AF_INET;
    listeningEndpoint.sin_addr.s_addr = INADDR_ANY;
    listeningEndpoint.sin_port = htons(port);

    int reuse = 1;
    if (setsockopt(listeningSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&reuse), sizeof(int)) == SOCKET_ERROR) {
        std::cerr << "Failed to set socket option for address reuse." << std::endl;
        closesocket(listeningSocket);
        WSACleanup();
        return 1;
    }

    if (bind(listeningSocket, reinterpret_cast<sockaddr*>(&listeningEndpoint), sizeof(listeningEndpoint)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind the socket." << std::endl;
        closesocket(listeningSocket);
        WSACleanup();
        return 1;
    }

    if (listen(listeningSocket, 10) == SOCKET_ERROR) {
        std::cerr << "Failed to listen on the socket." << std::endl;
        closesocket(listeningSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Listening on port " << port << " ..." << std::endl;

    while (true) {
        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);
        SOCKET conn = accept(listeningSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrSize);
        std::cout << "Connection opened" << std::endl;

        // Start a new session for each connection
        Session newSession(conn);
        newSession.Start();

        // Handle HTTP response asynchronously using a thread
        std::thread([&newSession]() {
            // Simulate receiving an HTTP response (replace with actual socket code)
            std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Length: 123\r\n\r\nSample Content";
            newSession.HandleHttpResponse(httpResponse);
        }).detach();
    }

    closesocket(listeningSocket);
    WSACleanup();

    return 0;
}
#pragma clang diagnostic pop