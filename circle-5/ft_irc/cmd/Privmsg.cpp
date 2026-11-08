#include "../inc/Server.hpp"

// PRIVMSG <target>{,<target>} :<text>     a target is a #channel or a nickname
// NOTICE works the same way, but never answers with an error (RFC 2812).
void Server::cmdPrivmsg(int fd, const Args &args, bool isNotice)
{
	std::string command = isNotice ? "NOTICE" : "PRIVMSG";

	if (args.empty() || args[0].empty())
	{
		if (!isNotice)
			reply(fd, ERR_NORECIPIENT, ":No recipient given (" + command + ")");
		return;
	}
	if (args.size() < 2 || args[1].empty())
	{
		if (!isNotice)
			reply(fd, ERR_NOTEXTTOSEND, ":No text to send");
		return;
	}

	Args targets = splitList(args[0]);
	for (size_t i = 0; i < targets.size(); i++)
	{
		std::string message = ":" + clients[fd].prefix() + " " + command + " " + targets[i] + " :" + args[1];

		if (targets[i][0] == '#')
		{
			Channel *channel = findChannel(targets[i]);
			if (channel != NULL && channel->isMember(fd))
				sendToChannel(*channel, message, fd);	// everyone in the channel except the sender
			else if (!isNotice && channel == NULL)
				reply(fd, ERR_NOSUCHCHANNEL, targets[i] + " :No such channel");
			else if (!isNotice)
				reply(fd, ERR_CANNOTSENDTOCHAN, targets[i] + " :Cannot send to channel");
		}
		else
		{
			Client *receiver = findClient(targets[i]);
			if (receiver != NULL)
				sendTo(receiver->fd, message);
			else if (!isNotice)
				reply(fd, ERR_NOSUCHNICK, targets[i] + " :No such nick/channel");
		}
	}
}
