#pragma once

#include <winsock2.h>
#include <string>

using std::string;

class TcpException : public std::exception {
public:
    TcpException(const char* message);
    const char* what() const noexcept override;

private:
    std::string errorMessage;
};

class TcpConnection
{
private:
	WSADATA wsaData;
	SOCKET connectionSocket;

public:
	TcpConnection(string ip, int port);
    TcpConnection(int port);
	~TcpConnection();

	void put(string buffer) const;
	string get(int maxLength) const;

	void close();
};
