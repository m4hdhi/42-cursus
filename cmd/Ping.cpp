#include "../inc/Server.hpp"

// PING <token>: the client checks that the server is alive. We answer PONG <token>.
void Server::cmdPing(int fd, const Args &args)
{
	if (args.empty())
		reply(fd, ERR_NOORIGIN, ":No origin specified");
	else
		sendTo(fd, ":" SERVER_NAME " PONG " SERVER_NAME " :" + args[0]);
}
