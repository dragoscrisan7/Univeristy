#include "TcpConnection.h"

#include <ws2tcpip.h>

typedef TcpException exception;

TcpConnection::TcpConnection(string ip, string port)
{
	int r;

	// WSAStartup
	if (WSAStartup(MAKEWORD(2, 2), &(this->wsaData)) != 0)
		throw exception("WSAStartul failed.");

	// Socket
	if ((this->clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
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
	if ((r = getaddrinfo(ip.c_str(), port.c_str(), &hints, &(serverInfo))) != 0) {
		auto excection = exception((string("GetAddrInfo failed: ") + std::to_string(r)).c_str());
		closesocket(this->clientSocket);
		WSACleanup();
		throw excection;
	}

	// Connect
	if (connect(this->clientSocket, serverInfo->ai_addr, (int)serverInfo->ai_addrlen) == SOCKET_ERROR) {
		auto excection = exception((string("Unable to connect to server: ") + std::to_string(WSAGetLastError())).c_str());
		closesocket(this->clientSocket);
		this->clientSocket = INVALID_SOCKET;
		WSACleanup();
		throw excection;
	}
	freeaddrinfo(serverInfo);
	serverInfo = NULL;
}

TcpConnection::~TcpConnection()
{
	this->close();
}

void TcpConnection::put(string buffer) const
{
	if (this->clientSocket == INVALID_SOCKET)
		throw exception("Connection closed.");

	if (send(this->clientSocket, buffer.c_str(), (int) buffer.length(), 0) == SOCKET_ERROR)
		throw exception((string("Put failed: ") + std::to_string(WSAGetLastError())).c_str());
}

string TcpConnection::get(int maxLength) const
{
	if (this->clientSocket == INVALID_SOCKET)
		throw exception("Connection closed.");

	char* buffer = new char[maxLength];
	int size = recv(this->clientSocket, buffer, maxLength, 0);

	if (size == 0) throw exception("Connection closed.");
	if (size < 0) throw exception((string("Get failed: ") + std::to_string(WSAGetLastError())).c_str());

	string result(buffer);
	delete[] buffer;
	return result;
}

void TcpConnection::close()
{
	if (this->clientSocket == INVALID_SOCKET) return;

	closesocket(this->clientSocket);
	WSACleanup();

	this->clientSocket = INVALID_SOCKET;
	this->wsaData = WSADATA();
}

TcpException::TcpException(const char* message) : std::exception((string("TCP Exception: ") + string(message)).c_str()) {}
