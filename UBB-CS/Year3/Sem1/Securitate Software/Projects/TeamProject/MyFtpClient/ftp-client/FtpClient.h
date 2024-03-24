#pragma once

#include "TcpConnection.h"

enum FtpMode { active, passive };
enum FtpType { binary, text };

class FtpClient
{
private:
    string controlHost;
    int controlPort;
    TcpConnection controlConnection;

    string dataHost = "";
    int dataPort = 0;
    TcpConnection* dataConnection;
    FtpMode mode = passive;

    string lastMessage;

    void begin();
    void end();
public:
	static const int MAX_CONTROL_SIZE = 1024;

    FtpClient(string host, int port=21);
    ~FtpClient();

	inline string message();

    string login(string username, string password = "");
    string disconnect();

    string setMode(FtpMode mode = passive);

    string list(string dir = "");
    string download(string path, FtpType type);
    string upload(string filename, FtpType type);
};

class FtpException : public std::exception {
public:
    FtpException(const char* message);
    const char* what() const noexcept override;

private:
    std::string errorMessage;
};