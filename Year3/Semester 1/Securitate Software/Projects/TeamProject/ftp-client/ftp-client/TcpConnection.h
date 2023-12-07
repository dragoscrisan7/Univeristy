#pragma once

#include <winsock2.h>
#include <string>

using std::string;

class TcpConnection
{
private:
	WSADATA wsaData;
	SOCKET clientSocket;

public:
	TcpConnection(string ip, string port);
	~TcpConnection();

	void put(string buffer) const;
	string get(int maxLength) const;

	void close();
};

class TcpException : public std::exception {
public:
	TcpException(const char* message);
};
