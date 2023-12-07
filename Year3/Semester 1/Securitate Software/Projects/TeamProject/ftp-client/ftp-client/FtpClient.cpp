#include "FtpClient.h"

#include <sstream>

using std::exception;
using std::stringstream;

FtpClient::FtpClient(string host) :
	host(host),
	controlConnection(host, string("21")),
	dataConnection(NULL)
{
	lastMessage = controlConnection.get(MAX_CONTROL_SIZE);

	stringstream sin(lastMessage);
	int code;
	sin >> code;

	if (code != 220)
		throw exception(lastMessage.c_str());
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
		throw exception(message.c_str());
	sout << message << std::endl;


	// PASS
	controlConnection.put(string("pass ") + password + string("\r\n"));
	message = controlConnection.get(MAX_CONTROL_SIZE);
	sin = stringstream(message);
	sin >> code;

	if (code != 230)
		throw exception(message.c_str());
	sout << message << std::endl;

	// return
	this->lastMessage = sout.str();
	return this->message();
}
