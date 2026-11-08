#include "../inc/Server.hpp"

// PART <#channel>{,<#channel>} [:<reason>]: leaves one or more channels.
void Server::cmdPart(int fd, const Args &args)
{
	if (args.empty())
	{
		reply(fd, ERR_NEEDMOREPARAMS, "PART :Not enough parameters");
		return;
	}
	Args names = splitList(args[0]);
	for (size_t i = 0; i < names.size(); i++)
	{
		Channel *channel = findChannel(names[i]);

		if (channel == NULL)
			reply(fd, ERR_NOSUCHCHANNEL, names[i] + " :No such channel");
		else if (!channel->isMember(fd))
			reply(fd, ERR_NOTONCHANNEL, names[i] + " :You're not on that channel");
		else
		{
			std::string message = ":" + clients[fd].prefix() + " PART " + names[i];
			if (args.size() > 1)
				message += " :" + args[1];
			sendToChannel(*channel, message);
			removeFromChannel(names[i], fd);
		}
	}
}
