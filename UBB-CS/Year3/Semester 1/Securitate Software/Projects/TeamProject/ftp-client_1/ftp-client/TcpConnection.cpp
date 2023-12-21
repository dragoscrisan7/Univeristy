#include "TcpConnection.h"

#include <ws2tcpip.h>

typedef TcpException exception;

TcpConnection::TcpConnection(string ip, int port)
{
	int r;

	// WSAStartup
	if (WSAStartup(MAKEWORD(2, 2), &(this->wsaData)) != 0)
		throw exception("WSAStartup failed.");

	// Socket
	if ((this->connectionSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		auto excection = exception((string("Error at socket: ") + std::to_string(WSAGetLastError())).c_str());
		WSACleanup();
		throw excection;
	}

	// Remote
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	addrinfo* serverInfo = NULL;
	if ((r = getaddrinfo(ip.c_str(), std::to_string(port).c_str(), &hints, &(serverInfo))) != 0) {
		auto excection = exception((string("GetAddrInfo failed: ") + std::to_string(r)).c_str());
		closesocket(this->connectionSocket);
		WSACleanup();
		throw excection;
	}

	// Connect
	if (connect(this->connectionSocket, serverInfo->ai_addr, (int)serverInfo->ai_addrlen) == SOCKET_ERROR) {
		auto excection = exception((string("Unable to connect to server: ") + std::to_string(WSAGetLastError())).c_str());
		closesocket(this->connectionSocket);
		this->connectionSocket = INVALID_SOCKET;
		WSACleanup();
		throw excection;
	}
	freeaddrinfo(serverInfo);
	serverInfo = NULL;
}

TcpConnection::TcpConnection(int port)
{
    int r;
    SOCKET listenSocket;

    // WSAStartup
    if (WSAStartup(MAKEWORD(2, 2), &(this->wsaData)) != 0)
        throw TcpException("WSAStartul failed.");

    // Socket
    if ((listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        auto ex = TcpException((string("Error at socket: ") + std::to_string(WSAGetLastError())).c_str());
        WSACleanup();
        throw ex;
    }

    // Bind
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htonl(port);

    if ((r = bind(listenSocket, (SOCKADDR *) &service, sizeof(service))) != 0) {
        auto ex = TcpException((string("Binding failed: ") + std::to_string(r)).c_str());
        closesocket(listenSocket);
        WSACleanup();
        throw ex;
    }

    // Listen
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        auto ex = TcpException((string("Unable to listen for connections: ") + std::to_string(WSAGetLastError())).c_str());
        closesocket(listenSocket);
        this->connectionSocket = INVALID_SOCKET;
        WSACleanup();
        throw ex;
    }

    // Accept
    if ((this->connectionSocket = accept(listenSocket, NULL, NULL)) == INVALID_SOCKET) {
        auto ex = TcpException((string("Unable to accept incoming connections: ") + std::to_string(WSAGetLastError())).c_str());
        closesocket(listenSocket);
        this->connectionSocket = INVALID_SOCKET;
        WSACleanup();
        throw ex;
    }

    closesocket(listenSocket);
}


TcpConnection::~TcpConnection()
{
	this->close();
}

void TcpConnection::put(string buffer) const
{
	if (this->connectionSocket == INVALID_SOCKET)
		throw exception("Connection closed.");

	if (send(this->connectionSocket, buffer.c_str(), (int) buffer.length(), 0) == SOCKET_ERROR)
		throw exception((string("Put failed: ") + std::to_string(WSAGetLastError())).c_str());
}

string TcpConnection::get(int maxLength) const
{
	if (this->connectionSocket == INVALID_SOCKET)
		throw exception("Connection closed.");

	char* buffer = new char[maxLength];
	int size = recv(this->connectionSocket, buffer, maxLength, 0);

	if (size == 0) throw exception("Connection closed.");
	if (size < 0) throw exception((string("Get failed: ") + std::to_string(WSAGetLastError())).c_str());

    std::string result(buffer, size);

    delete[] buffer;
    return result;
}

void TcpConnection::close()
{
	if (this->connectionSocket == INVALID_SOCKET) return;

	closesocket(this->connectionSocket);
	WSACleanup();

	this->connectionSocket = INVALID_SOCKET;
	this->wsaData = WSADATA();
}

TcpException::TcpException(const char* message) : errorMessage("TCP Exception: ") {
    errorMessage += message;
}

const char* TcpException::what() const noexcept {
    return errorMessage.c_str();
}