#include "FtpClient.h"

#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>

using std::exception;
using std::stringstream;

void FtpClient::begin()
{
    if (passive)
        this->dataConnection = new TcpConnection(dataHost, dataPort);
    else
        this->dataConnection = new TcpConnection(dataPort);
}

void FtpClient::end()
{
    delete this->dataConnection;
}

FtpClient::FtpClient(string host, int port) :
        controlHost(host),
        controlPort(port),
        controlConnection(host, port),
        dataConnection(NULL)
{
    string message = controlConnection.get(MAX_CONTROL_SIZE);

    stringstream sin(message);
    int code;
    sin >> code;

    if (code != 220)
        throw FtpException(lastMessage.c_str());

    lastMessage = message + "\n" + setMode();
}

FtpClient::~FtpClient()
{
    disconnect();
}

inline string FtpClient::message()
{
	return this->lastMessage;
}

string FtpClient::login(string username, string password)
{
    stringstream sout, sin;
    string message;
    int code;

    // USER
    controlConnection.put(string("USER ") + username + string("\r\n"));
    message = controlConnection.get(MAX_CONTROL_SIZE);
    sin = stringstream(message);
    sin >> code;

    if (code == 230 || code == 220)
        return message;
    if (code != 331)
        throw FtpException(message.c_str());
    sout << message << std::endl;


    // PASS
    controlConnection.put(string("PASS ") + password + string("\r\n"));
    message = controlConnection.get(MAX_CONTROL_SIZE);
    sin = stringstream(message);
    sin >> code;

    if (code != 230)
        throw FtpException(message.c_str());
    sout << message << std::endl;

    // return
    this->lastMessage = sout.str();
    return this->message();
}

string FtpClient::disconnect()
{
    controlConnection.put(string("QUIT\r\n"));

    string message = controlConnection.get(MAX_CONTROL_SIZE);

    stringstream sin(message);
    int code;

    sin >> code;

    if (code != 221)
        throw FtpException(message.c_str());

    this->controlConnection.close();
    delete this->dataConnection;

    this->lastMessage = message;
    return this->lastMessage;
}

string FtpClient::setMode(FtpMode mode)
{
    switch (mode) {
        case active: {
            if (this->mode == active)
                throw FtpException("Mode already set to active.");

            throw FtpClient("Client does not support active mode.");
        }
        case passive: {
//            if (this->mode == passive)
//                throw FtpException("Mode already set to pasive.");

            controlConnection.put("PASV\r\n");

            string message = controlConnection.get(MAX_CONTROL_SIZE);

            stringstream sin(message);
            int code;

            sin >> code;
            if (code != 227)
                throw FtpException(message.c_str());

            size_t openParenPos = message.find('(');
            if (openParenPos == std::string::npos) {
                throw std::runtime_error("Opening parenthesis not found in message.");
            }

            // Find the position of the closing parenthesis
            size_t closeParenPos = message.find(')', openParenPos);
            if (closeParenPos == std::string::npos) {
                throw std::runtime_error("Closing parenthesis not found in message.");
            }

            // Extract the substring between parentheses
            std::string dataSubstring = message.substr(openParenPos + 1, closeParenPos - openParenPos - 1);


            int bytes[6];
            if (sscanf(dataSubstring.c_str(), "%d,%d,%d,%d,%d,%d", &bytes[0], &bytes[1], &bytes[2], &bytes[3], &bytes[4], &bytes[5]) != 6) {
                throw std::runtime_error("Error extracting values from message.");
            }

            this->dataHost = std::to_string(bytes[0]) + "." + std::to_string(bytes[1]) + "." + std::to_string(bytes[2]) + "." + std::to_string(bytes[3]);
            this->dataPort = bytes[4] * 256 + bytes[5];

            this->mode = passive;

            this->lastMessage = message;
            return this->lastMessage;
        }
        default: {
            throw FtpException("Invalid tcp mode.");
        }
    }
}

string FtpClient::list(string dir)
{
    string message;
    stringstream sin;
    int code;

    controlConnection.put(dir.length() == 0 ? "LIST\r\n" : ("LIST " + dir + "\r\n"));

    message = controlConnection.get(MAX_CONTROL_SIZE);
    sin = stringstream{ message };
    sin >> code;
    if (code != 150)
        throw FtpException(message.c_str());
    this->lastMessage = message;

    begin();

    message = controlConnection.get(MAX_CONTROL_SIZE);
    sin = stringstream{ message };
    sin >> code;
    if (code != 226)
        throw FtpException(message.c_str());
    this->lastMessage += "\n" + message;

    string part, result = "";
    int max_length = 1024;
    while (true) {
        part = dataConnection->get(max_length);
        result += part;
        if (part.length() < max_length) {
            break;
        }
    }
    end();

    return result;
}

string FtpClient::download(string path, FtpType type)
{
    string message;
    stringstream sin;
    int code;

    switch (type) {
        case binary: {
            controlConnection.put("TYPE I\r\n");
            break;
        }
        case text: {
            controlConnection.put("TYPE A\r\n");
            break;
        }
        default: {
            throw FtpException("Invalid FTP type.");
        }
    }

    message = controlConnection.get(MAX_CONTROL_SIZE);
    sin = stringstream{ message };
    sin >> code;
    if (code != 200)
        throw FtpException(message.c_str());
    this->lastMessage = message;

    controlConnection.put("RETR " + path + "\r\n");

    message = controlConnection.get(MAX_CONTROL_SIZE);
    sin = stringstream{ message };
    sin >> code;
    if (code != 150)
        throw FtpException(message.c_str());
    this->lastMessage += "\n" + message;

    begin();

    message = controlConnection.get(MAX_CONTROL_SIZE);
    sin = stringstream{ message };
    sin >> code;
    if (code != 226)
        throw FtpException(message.c_str());
    this->lastMessage += "\n" + message;

    string part;
    int max_length = 1024;
    std::ofstream fout(path);
    while (true){
        part = dataConnection->get(max_length);
        fout << part;

        if (part.length() < max_length) {
            break;
        }
    }
    end();
    fout.close();

    return this->lastMessage;
}

string FtpClient::upload(string filename, FtpType type)
{
    string message;
    stringstream sin;
    int code;

    switch (type) {
        case binary: {
            controlConnection.put("TYPE I\r\n");
            break;
        }
        case text: {
            controlConnection.put("TYPE A\r\n");
            break;
        }
        default: {
            throw FtpException("Invalid FTP type.");
        }
    }

    message = controlConnection.get(MAX_CONTROL_SIZE);
    sin = stringstream{ message };
    sin >> code;
    if (code != 200)
        throw FtpException(message.c_str());
    this->lastMessage = message;

    controlConnection.put("STOR " + filename + "\r\n");

    begin();

    message = controlConnection.get(MAX_CONTROL_SIZE);
    sin = stringstream{ message };
    sin >> code;
    if (code != 150)
        throw FtpException(message.c_str());
    this->lastMessage += "\n" + message;

    string part, result = "";
    int max_length = 1024;
    std::ifstream fin(filename);
    while (std::getline(fin, part))
        result += "\n" + part;
    fin.close();

    dataConnection->put(result);
    end();

    message = controlConnection.get(MAX_CONTROL_SIZE);
    sin = stringstream{ message };
    sin >> code;
    if (code != 226)
        throw FtpException(message.c_str());
    this->lastMessage += "\n" + message;

    return this->lastMessage;
}

FtpException::FtpException(const char* message) : errorMessage("Ftp Exception: ") {
    errorMessage += message;
}

const char* FtpException::what() const noexcept {
    return errorMessage.c_str();
}