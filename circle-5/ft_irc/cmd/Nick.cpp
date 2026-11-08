#include "../inc/Server.hpp"

// NICK <nickname>: sets the nickname, or changes it later.
void Server::cmdNick(int fd, const Args &args)
{
	Client		&client = clients[fd];
	std::string	nickname = args.empty() ? "" : args[0];
	Client		*owner = findClient(nickname);

	if (!client.passwordOk)
		reply(fd, ERR_NOTREGISTERED, ":You must send PASS first");
	else if (nickname.empty())
		reply(fd, ERR_NONICKNAMEGIVEN, ":No nickname given");
	else if (!isValidNickname(nickname))
		reply(fd, ERR_ERRONEUSNICKNAME, nickname + " :Erroneous nickname");
	else if (owner != NULL && owner != &client)
		reply(fd, ERR_NICKNAMEINUSE, nickname + " :Nickname is already in use");
	else if (nickname != client.nickname)
	{
		if (client.registered)	// tell the user and everyone in their channels
		{
			std::string message = ":" + client.prefix() + " NICK :" + nickname;
			sendTo(fd, message);
			sendToPeers(fd, message);
		}
		client.nickname = nickname;
		tryToRegister(fd);
	}
}
