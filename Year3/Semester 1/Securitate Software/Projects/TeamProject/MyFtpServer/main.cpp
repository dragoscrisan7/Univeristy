/*FTP server*/
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

/*for getting file size using stat()*/
#include<sys/stat.h>

/*for O_RDONLY*/
#include<fcntl.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")
const int BUFFER_SIZE = 1024;
const int DEFAULT_PORT = 21;

// Function to send response to the client
void sendResponse(SOCKET clientSocket, const std::string& response) {
    send(clientSocket, response.c_str(), response.length(), 0);
}

// Function to receive command from the client
std::string receiveCommand(SOCKET clientSocket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    return std::string(buffer);
}

// Function to parse FTP command
std::string parseCommand(const std::string& command) {
    // Implement parsing logic based on your needs
    // For simplicity, returning the full command as a string
    return command;
}

// Function to execute FTP command
std::string executeCommand(const std::string& command) {
    // Implement command execution logic based on your needs
    // For simplicity, returning a generic response
    return "200 Command OK\r\n";
}

int main(int argc, char* argv[]) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error initializing Winsock\n";
        return EXIT_FAILURE;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket\n";
        WSACleanup();
        return EXIT_FAILURE;
    }

    // Bind the socket
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(DEFAULT_PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error binding socket\n";
        closesocket(serverSocket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        std::cerr << "Error listening for connections\n";
        closesocket(serverSocket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    std::cout << "FTP Server listening on port " << DEFAULT_PORT << std::endl;

    while (true) {
        // Accept incoming connection
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error accepting connection\n";
            continue;
        }

        // Send welcome message
        sendResponse(clientSocket, "220 Welcome to FTP Server\r\n");

        // Handle FTP commands in a loop
        while (true) {
            // Receive and parse FTP command
            std::string command = parseCommand(receiveCommand(clientSocket));

            // Execute command
            std::string response = executeCommand(command);

            // Send response to the client
            sendResponse(clientSocket, response);

            // Close data connections if necessary
            // (Not implemented in this simplified example)

            // Close the connection on QUIT command
            if (command.find("QUIT") != std::string::npos) {
                sendResponse(clientSocket, "221 Goodbye!\r\n");
                closesocket(clientSocket);
                break;
            }
        }
    }

    closesocket(serverSocket);

    // Cleanup Winsock
    WSACleanup();

    return EXIT_SUCCESS;
}