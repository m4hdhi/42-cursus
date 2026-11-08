#include "../inc/Server.hpp"

// USER <username> <mode> <unused> :<real name>   e.g. USER alice 0 * :Alice Smith
void Server::cmdUser(int fd, const Args &args)
{
	Client &client = clients[fd];

	if (client.registered)
		reply(fd, ERR_ALREADYREGISTERED, ":You may not reregister");
	else if (!client.passwordOk)
		reply(fd, ERR_NOTREGISTERED, ":You must send PASS first");
	else if (args.size() < 4 || args[0].empty())
		reply(fd, ERR_NEEDMOREPARAMS, "USER :Not enough parameters");
	else
	{
		client.username = args[0];
		client.realname = args[3];
		tryToRegister(fd);
	}
}
