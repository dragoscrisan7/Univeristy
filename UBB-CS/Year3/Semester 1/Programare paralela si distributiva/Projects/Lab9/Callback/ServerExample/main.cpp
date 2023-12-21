#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")


class Session {
public:
    Session(SOCKET conn) : _conn(conn), _pos(0), _size(0), _state(State::BeforeFirst), _a(0), _b(0) {
        _buffer = new char[10];
    }

    void Start() {
        _pos = 0;
        _state = State::BeforeFirst;
        _a = 0;
        _b = 0;
        OnBytesReceived(0); // Start the process as the C# version does
    }

private:

    void OnBytesReceived(int bytesRead) {
        _size = recv(_conn, _buffer, 10, 0);
        _pos = 0;
        ProcessBuffer();
    }

    void SendSum(bool isLast) {
        std::string s = std::to_string(_a + _b);
        std::string toSendStr = s + "\n";
        send(_conn, toSendStr.c_str(), static_cast<int>(toSendStr.size()), 0);

        if (isLast) {
            closesocket(_conn);
        } else {
            OnSendDone(0); // Continue the process as the C# version does
        }
    }

    void OnSendDone(int) {
        OnBytesReceived(0); // Continue the process as the C# version does
    }

    void ProcessBuffer() {
        if (_size == 0) {
            switch (_state) {
                case State::BeforeFirst:
                    std::cout << "Connection closed" << std::endl;
                    closesocket(_conn);
                    return;
                case State::ReadingSecond:
                    SendSum(true);
                    return;
                default:
                    std::cout << "Connection closed prematurely" << std::endl;
                    closesocket(_conn);
                    return;
            }
        }

        while (_pos < _size) {
            char c = _buffer[_pos];
            ++_pos;

            if (c == '\n' || c == '\r' || c == '\t') {
                c = ' ';
            } else if (c != ' ' && (c < '0' || c > '9')) {
                std::cout << "Unexpected character: " << c << std::endl;
                c = ' ';
            }

            switch (_state) {
                case State::BeforeFirst:
                    if (c >= '0' && c <= '9') {
                        _state = State::ReadingFirst;
                        _a = c - '0';
                    }
                    break;
                case State::ReadingFirst:
                    if (c >= '0' && c <= '9') {
                        _a = _a * 10 + (c - '0');
                    } else {
                        _state = State::BeforeSecond;
                    }
                    break;
                case State::BeforeSecond:
                    if (c >= '0' && c <= '9') {
                        _state = State::ReadingSecond;
                        _b = c - '0';
                    }
                    break;
                case State::ReadingSecond:
                    if (c >= '0' && c <= '9') {
                        _b = _b * 10 + (c - '0');
                    } else {
                        _state = State::BeforeFirst;
                        SendSum(false);
                        return;
                    }
                    break;
            }
        }
    }

public:
    static void OnNewConnection(SOCKET listeningSocket, int) {
        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);
        SOCKET conn = accept(listeningSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrSize);
        std::cout << "Connection opened" << std::endl;
        Session newSession(conn);
        newSession.Start();
    }
private:
    enum class State { BeforeFirst, ReadingFirst, BeforeSecond, ReadingSecond };
    SOCKET _conn;
    char* _buffer;
    int _pos;
    int _size;
    State _state;
    int _a, _b;

    // Rest of the Session class methods...
};

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

    // Allow reuse of the address (SO_REUSEADDR) to avoid "failed to bind" errors.
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
        Session::OnNewConnection(listeningSocket, 0);
    }

    closesocket(listeningSocket);
    WSACleanup();

    return 0;
}
