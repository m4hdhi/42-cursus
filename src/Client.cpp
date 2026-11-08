#include "../inc/Client.hpp"

Client::Client() : fd(-1), passwordOk(false), registered(false), quitting(false), lineTooLong(false)
{
}

Client::Client(int clientFd, const std::string &clientIp)
	: fd(clientFd), ip(clientIp), passwordOk(false), registered(false), quitting(false), lineTooLong(false)
{
}

std::string Client::prefix() const
{
	return nickname + "!" + username + "@" + ip;
}
