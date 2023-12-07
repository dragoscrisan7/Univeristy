#pragma once

#include "TcpConnection.h"

class FtpClient
{
private:
	string host;
	TcpConnection controlConnection;
	TcpConnection* dataConnection;
	string lastMessage;
public:
	static const int MAX_CONTROL_SIZE = 1024;

	FtpClient(string host);

	inline string message();
	string login(string username, string password = "");
};

