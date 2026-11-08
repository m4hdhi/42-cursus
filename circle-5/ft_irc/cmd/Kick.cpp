#include "../inc/Server.hpp"

// KICK <#channel> <nickname> [:<reason>]: an operator removes someone from a channel.
void Server::cmdKick(int fd, const Args &args)
{
	if (args.size() < 2)
	{
		reply(fd, ERR_NEEDMOREPARAMS, "KICK :Not enough parameters");
		return;
	}
	Channel	*channel = findChannel(args[0]);
	Client	*target = findClient(args[1]);

	if (channel == NULL)
		reply(fd, ERR_NOSUCHCHANNEL, args[0] + " :No such channel");
	else if (!channel->isMember(fd))
		reply(fd, ERR_NOTONCHANNEL, args[0] + " :You're not on that channel");
	else if (!channel->isOperator(fd))
		reply(fd, ERR_CHANOPRIVSNEEDED, args[0] + " :You're not channel operator");
	else if (target == NULL || !channel->isMember(target->fd))
		reply(fd, ERR_USERNOTINCHANNEL, args[1] + " " + args[0] + " :They aren't on that channel");
	else
	{
		std::string reason = args.size() > 2 ? args[2] : clients[fd].nickname;
		sendToChannel(*channel, ":" + clients[fd].prefix() + " KICK " + args[0] + " " + args[1] + " :" + reason);
		removeFromChannel(args[0], target->fd);
	}
}
