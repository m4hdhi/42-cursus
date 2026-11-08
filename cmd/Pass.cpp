#include "../inc/Server.hpp"

// PASS <password>: must be sent first, before NICK and USER.
void Server::cmdPass(int fd, const Args &args)
{
	Client &client = clients[fd];

	if (client.registered)
		reply(fd, ERR_ALREADYREGISTERED, ":You may not reregister");
	else if (args.empty())
		reply(fd, ERR_NEEDMOREPARAMS, "PASS :Not enough parameters");
	else if (args[0] != password)
		reply(fd, ERR_PASSWDMISMATCH, ":Password incorrect");
	else
		client.passwordOk = true;
}
