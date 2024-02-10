#include "TcpConnection.h"

#include <ws2tcpip.h>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <filesystem>
#include <fstream>

typedef TcpException exception;

TcpConnection::TcpConnection(string port)
{
    if (WSAStartup(MAKEWORD(2, 2), &(this->wsaData)) != 0)
        throw std::runtime_error("WSAStartup failed.");

    /// Socket
    if ((this->serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        auto server_exception = exception((std::string("Error at socket: ") + std::to_string(WSAGetLastError())).c_str());
        WSACleanup();
        throw server_exception;
    }

    /// Local
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(std::stoi(port));

    /// Bind
    if (bind(this->serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        auto bind_exception = exception ((std::string("Error at bind: ") + std::to_string(WSAGetLastError())).c_str());
        closesocket(this->serverSocket);
        WSACleanup();
        throw bind_exception;
    }
}

TcpConnection::~TcpConnection()
{
    closesocket(this->serverSocket);
    WSACleanup();
}

void TcpConnection::startListening() {
    /// Listen
    if (listen(this->serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error listening for connections" << std::endl;
        return;
    }

    std::cout << "Server listening for connections..." << std::endl;

    while (true) {
        /// Accept a connection
        sockaddr_in clientAddress;
        int clientAddrSize = sizeof(clientAddress);
        SOCKET clientSocket = accept(this->serverSocket, (struct sockaddr*)&clientAddress, &clientAddrSize);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }

        std::string welcomeMessage = "220 Welcome to FTP server\r\n";
        send(clientSocket, welcomeMessage.c_str(), welcomeMessage.length(), 0);

        ///Thread for client
        std::thread(&TcpConnection::handleClient, this, clientSocket).detach();
    }
}

void TcpConnection::handleClient(SOCKET clientSocket) {
    char buffer[MAX_CONTROL_SIZE];
    SOCKET dataSocket = INVALID_SOCKET;
    SOCKET dataClientSocket = INVALID_SOCKET;

    try {
        std::cout << "New client connected" << std::endl;

        while (true) {
            int size = recv(clientSocket, buffer, MAX_CONTROL_SIZE, 0);
            if (size < 0) {
                std::cerr << "Error receiving data from client." << std::endl;
                break;
            }

            std::string receivedData(buffer, size);

            size_t crlfPos = receivedData.find("\r\n");
            if (crlfPos != std::string::npos) {
                std::string command = receivedData.substr(0, crlfPos);

                if (command.substr(0, 4) == "USER") {
                    loggedInUsername = command.substr(5);
                    send(clientSocket, "331 Password required\r\n", 24, 0); ///username
                } else if (command.substr(0, 4) == "PASS") {
                    std::string password = command.substr(5);
                    if (login(loggedInUsername, password)) {
                        send(clientSocket, "230 User logged in\r\n", 22, 0); ///password and login
                    } else {
                        send(clientSocket, "530 Login incorrect\r\n", 23, 0);
                    }
                } else if (command.substr(0, 4) == "QUIT") {
                    isLoggedIn = false;
                    send(clientSocket, "221 Goodbye\r\n", 14, 0);///logout

                    break;
                } else if (command.substr(0, 4) == "PASV") {
                    int dataPort = 1024 + rand() % (65535 - 1024 + 1);
                    dataSocket = openDataSocket(dataPort);///passive data socket open

                    sendPortCommand(dataPort, clientSocket);///passive port send

                    std::cout << "Data connection accepted from client" << std::endl;
                } else if (command.substr(0, 4) == "LIST") {
                    size_t spacePos = command.find(' ');
                    std::string dir;

                    if (spacePos != std::string::npos) {
                        dir = command.substr(spacePos + 1);
                        dir.erase(dir.find_last_not_of("\r\n") + 1);
                    }

                    send(clientSocket, "150 Socket accepting.\r\n", 25, 0);
                    SOCKET dataClientSocket = accept(dataSocket, nullptr, nullptr);
                    if (dataClientSocket == INVALID_SOCKET) {
                        std::cerr << "Error accepting data connection." << std::endl;
                    } else {
                        std::thread dataConnectionThread(&TcpConnection::handleListCommand, this, dataClientSocket, dir);
                        dataConnectionThread.detach();
                    }

                    send(clientSocket, "226 Directory send OK.\r\n", 26, 0);
                } else if (command.substr(0, 4) == "TYPE"){
                    size_t spacePos = command.find(' ');
                    std::string transferType;

                    if (spacePos != std::string::npos) {
                        transferType = command.substr(spacePos + 1);
                        transferType.erase(transferType.find_last_not_of("\r\n") + 1);
                    }

                    if (transferType == "A") {
                        this->selectedTransferType = transferType;
                        send(clientSocket, "200 ASCII Type selected.\r\n", 29, 0);
                    } else if (transferType == "I") {
                        this->selectedTransferType = transferType;
                        send(clientSocket, "200 Binary Type selected.\r\n", 30, 0);
                    } else {
                        send(clientSocket, "504 Command not implemented for that parameter.\r\n", 48, 0);
                    }
                } else if (command.substr(0, 4) == "RETR"){
                    size_t spacePos = command.find(' ');
                    std::string filePath;

                    if (spacePos != std::string::npos) {
                        filePath = command.substr(spacePos + 1);
                        filePath.erase(filePath.find_last_not_of("\r\n") + 1);
                    }

                    send(clientSocket, "150 Socket accepting.\r\n", 25, 0);
                    SOCKET dataClientSocket = accept(dataSocket, nullptr, nullptr);
                    if (dataClientSocket == INVALID_SOCKET) {
                        std::cerr << "Error accepting data connection." << std::endl;
                    } else {
                        std::thread dataConnectionThread(&TcpConnection::handleUploadCommand, this, dataClientSocket, filePath, clientSocket);
                        dataConnectionThread.detach();
                    }
                } else if (command.substr(0, 4) == "STOR"){
                    size_t spacePos = command.find(' ');
                    std::string filePath;

                    if (spacePos != std::string::npos) {
                        filePath = command.substr(spacePos + 1);
                        filePath.erase(filePath.find_last_not_of("\r\n") + 1);
                    }

                    send(clientSocket, "150 Socket accepting.\r\n", 25, 0);
                    SOCKET dataClientSocket = accept(dataSocket, nullptr, nullptr);
                    if (dataClientSocket == INVALID_SOCKET) {
                        std::cerr << "Error accepting data connection." << std::endl;
                    } else {
                        std::thread dataConnectionThread(&TcpConnection::handleDownloadCommand, this, dataClientSocket, filePath, clientSocket);
                        dataConnectionThread.detach();
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in client handler: " << e.what() << std::endl;
    }

    closesocket(clientSocket);
    if (dataSocket != INVALID_SOCKET) {
        closesocket(dataSocket);
        closesocket(dataClientSocket);
    }

    std::cout << "Client disconnected" << std::endl;
}

bool TcpConnection::login(string username, string password) {
    std::lock_guard<std::mutex> lock(loginMutex);
    if (username == "user" && password == "pass") {
        isLoggedIn = true;
        loggedInUsername = username;
        std::cout << "Client login successfully" << std::endl;
        return true;
    } else {
        isLoggedIn = false;
        loggedInUsername = "";
        return false;
    }
}

SOCKET TcpConnection::openDataSocket(int port) {
    SOCKET dataSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (dataSocket == INVALID_SOCKET) {
        throw TcpException("Error creating data socket.");
    }

    sockaddr_in dataAddr;
    dataAddr.sin_family = AF_INET;
    dataAddr.sin_addr.s_addr = INADDR_ANY;
    dataAddr.sin_port = htons(port);

    if (bind(dataSocket, (struct sockaddr*)&dataAddr, sizeof(dataAddr)) == SOCKET_ERROR) {
        closesocket(dataSocket);
        throw TcpException("Error binding data socket.");
    }

    if (listen(dataSocket, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(dataSocket);
        throw TcpException("Error listening on data socket.");
    }

    return dataSocket;
}

void TcpConnection::sendPortCommand(int dataPort, SOCKET clientSocket) {
    ///get ip
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    hostent* hostInfo = gethostbyname(hostname);
    in_addr* address = reinterpret_cast<in_addr*>(hostInfo->h_addr_list[0]);

    ///send port
    std::string portCommand = "227 (" + std::to_string(address->S_un.S_un_b.s_b1) + "," +
                              std::to_string(address->S_un.S_un_b.s_b2) + "," +
                              std::to_string(address->S_un.S_un_b.s_b3) + "," +
                              std::to_string(address->S_un.S_un_b.s_b4) + "," +
                              std::to_string(dataPort / 256) + "," +
                              std::to_string(dataPort % 256) + ")" + "\r\n";


    send(clientSocket, portCommand.c_str(), portCommand.length(), 0);
}

void TcpConnection::handleListCommand(SOCKET dataSocket, const string& dir) {
    try {
        std::string directoryListing = getDirectoryListing(dir);

        send(dataSocket, directoryListing.c_str(), directoryListing.length(), 0);
    } catch (const std::exception& e) {
        std::cerr << "Error handling LIST command: " << e.what() << std::endl;
    }

    closesocket(dataSocket);
}

std::string TcpConnection::getDirectoryListing(const std::string& dir) {
    std::string listing;

    std::filesystem::path currentPath = std::filesystem::current_path() / dir;
    for (const auto& entry : std::filesystem::directory_iterator(currentPath)) {
        listing += entry.path().filename().string() + "\r\n";
    }

    return listing;
}

void TcpConnection::handleUploadCommand(SOCKET dataSocket, const std::string& filePath, SOCKET clientSocket) {
    try {
        std::ifstream fileStream(filePath, std::ios::binary);

        if (!fileStream.is_open()) {
            std::cerr << "Error opening file: " << filePath << std::endl;
            return;
        }

        char buffer[MAX_CONTROL_SIZE];
        int bytesRead;

        if (selectedTransferType == "A") {
            // ASCII mode: read and send the file line by line
            std::string line;
            while (std::getline(fileStream, line)) {
                send(dataSocket, (line + "\r\n").c_str(), line.length() + 2, 0);
            }
        } else if (selectedTransferType == "I") {
            // Binary mode: read and send the file in binary
            while ((bytesRead = fileStream.readsome(buffer, MAX_CONTROL_SIZE)) > 0) {
                send(dataSocket, buffer, bytesRead, 0);
            }
        }

        send(clientSocket, "226 File sent OK\r\n", 19, 0);
        fileStream.close();
    } catch (const std::exception& e) {
        std::cerr << "Error handling RETR command: " << e.what() << std::endl;
        send(clientSocket, "550 File not found\r\n", 21, 0);
    }

    closesocket(dataSocket);
}

void TcpConnection::handleDownloadCommand(SOCKET dataSocket, const std::string& filePath, SOCKET clientSocket) {
    try {
        std::ofstream fileStream(filePath, std::ios::binary);

        if (!fileStream.is_open()) {
            std::cerr << "Error opening file: " << filePath << std::endl;
            send(clientSocket, "550 File unavailable.\r\n", 24, 0);
            return;
        }

        if (selectedTransferType == "A") {
            // ASCII mode: read and receive the file line by line
            std::string content = get(MAX_CONTROL_SIZE, dataSocket);
            fileStream << content;
        } else if (selectedTransferType == "I") {
            // Binary mode: read and receive the file in binary
            char buffer[MAX_CONTROL_SIZE];
            int bytesRead;
            while ((bytesRead = recv(dataSocket, buffer, MAX_CONTROL_SIZE, 0)) > 0) {
                fileStream.write(buffer, bytesRead);
            }
        }

        fileStream.close();
        send(clientSocket, "226 File transferred.\r\n", 24, 0);
    } catch (const std::exception& e) {
        std::cerr << "Error handling STOR command: " << e.what() << std::endl;
        send(clientSocket, "550 File not found\r\n", 21, 0);
    }

    closesocket(dataSocket);
}

std::string TcpConnection::get(int maxLength, SOCKET dataSocket) const {
    if (dataSocket == INVALID_SOCKET) {
        throw std::runtime_error("Connection closed.");
    }

    char* buffer = new char[maxLength];
    int size = recv(dataSocket, buffer, maxLength, 0);

    if (size == 0) {
        delete[] buffer;
        throw std::runtime_error("Connection closed.");
    }

    if (size < 0) {
        delete[] buffer;
        throw std::runtime_error("Get failed: " + std::to_string(WSAGetLastError()));
    }

    std::string result(buffer, size);
    delete[] buffer;
    return result;
}


TcpException::TcpException(const char* message) : errorMessage("TCP Exception: ") {
    errorMessage += message;
}

const char* TcpException::what() const noexcept {
    return errorMessage.c_str();
}