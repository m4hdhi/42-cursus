#include "../inc/Server.hpp"

// INVITE <nickname> <#channel>: an operator lets someone join the channel, even if it is +i, +k or +l.
// As the subject says, INVITE is an operator command: regular users always get 482.
void Server::cmdInvite(int fd, const Args &args)
{
	if (args.size() < 2)
	{
		reply(fd, ERR_NEEDMOREPARAMS, "INVITE :Not enough parameters");
		return;
	}
	Client	*target = findClient(args[0]);
	Channel	*channel = findChannel(args[1]);

	if (target == NULL)
		reply(fd, ERR_NOSUCHNICK, args[0] + " :No such nick/channel");
	else if (channel == NULL)
		reply(fd, ERR_NOSUCHCHANNEL, args[1] + " :No such channel");
	else if (!channel->isMember(fd))
		reply(fd, ERR_NOTONCHANNEL, args[1] + " :You're not on that channel");
	else if (!channel->isOperator(fd))
		reply(fd, ERR_CHANOPRIVSNEEDED, args[1] + " :You're not channel operator");
	else if (channel->isMember(target->fd))
		reply(fd, ERR_USERONCHANNEL, args[0] + " " + args[1] + " :is already on channel");
	else
	{
		channel->invited.insert(target->fd);
		reply(fd, RPL_INVITING, args[0] + " " + args[1]);
		sendTo(target->fd, ":" + clients[fd].prefix() + " INVITE " + args[0] + " " + args[1]);
	}
}
