#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <thread>
#include <future>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

class Session {
public:
    Session(SOCKET conn) : _conn(conn) {
        _buffer.resize(10);
    }

    char ReadNextChar() {
        if (_pos >= _size) {
            _pos = 0;
            _size = recv(_conn, &_buffer[0], static_cast<int>(_buffer.size()), 0);
            if (_size == 0) {
                return '\0';
            }
        }
        char c = _buffer[_pos];
        ++_pos;
        if (c == '\n' || c == '\r' || c == '\t') {
            c = ' ';
        } else if (c != ' ' && (c < '0' || c > '9')) {
            std::cerr << "Unexpected character: " << c << std::endl;
            c = ' ';
        }
        return c;
    }

    void Run() {
        _pos = 0;
        _size = recv(_conn, &_buffer[0], static_cast<int>(_buffer.size()), 0);
        int _a = 0;
        int _b = 0;
        char c = ReadNextChar();
        while (true) {
            while (c == ' ') {
                c = ReadNextChar();
            }
            if (c == '\0') {
                std::cout << "Connection closed" << std::endl;
                closesocket(_conn);
                return;
            }
            while (c != ' ') {
                if (c == '\0') {
                    std::cout << "Connection closed prematurely" << std::endl;
                    closesocket(_conn);
                    return;
                }
                _a = _a * 10 + (c - '0');
                c = ReadNextChar();
            }
            while (c == ' ') {
                c = ReadNextChar();
            }
            while (c != ' ') {
                if (c == '\0') {
                    SendSum(_a + _b);
                    std::cout << "Connection closed" << std::endl;
                    closesocket(_conn);
                    return;
                }
                _b = _b * 10 + (c - '0');
                c = ReadNextChar();
            }
            SendSum(_a + _b);
            _a = 0;
            _b = 0;
        }
    }

    void SendSum(int sum) {
        std::string s = std::to_string(sum);
        s.push_back('\n');
        send(_conn, s.c_str(), static_cast<int>(s.size()), 0);
    }

private:
    SOCKET _conn;
    std::vector<char> _buffer;
    size_t _pos;
    size_t _size;
};

[[noreturn]] void MainLoop(SOCKET listeningSocket) {
    while (true) {
        SOCKET conn = accept(listeningSocket, nullptr, nullptr);
        if (conn == INVALID_SOCKET) {
            std::cerr << "Failed to accept a connection." << std::endl;
            continue;
        }
        std::cout << "Connection opened" << std::endl;
        Session session(conn);
        session.Run();
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    int port = std::atoi(argv[1]);

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    SOCKET listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listeningSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create a socket." << std::endl;
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(listeningSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind to the port." << std::endl;
        return 1;
    }

    if (listen(listeningSocket, 10) == SOCKET_ERROR) {
        std::cerr << "Failed to listen for connections." << std::endl;
        return 1;
    }

    std::cout << "Listening on port " << port << "..." << std::endl;
    MainLoop(listeningSocket);

    closesocket(listeningSocket);
    WSACleanup();

    return 0;
}
