#include "../inc/Server.hpp"

// JOIN <#channel>{,<#channel>} [<key>{,<key>}]   e.g. JOIN #a,#b secretOfA
void Server::cmdJoin(int fd, const Args &args)
{
	if (args.empty())
	{
		reply(fd, ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters");
		return;
	}
	Args names = splitList(args[0]);
	Args keys;
	if (args.size() > 1)
		keys = splitList(args[1]);

	for (size_t i = 0; i < names.size(); i++)
		joinChannel(fd, names[i], i < keys.size() ? keys[i] : "");
}

void Server::joinChannel(int fd, const std::string &name, const std::string &key)
{
	if (!isValidChannelName(name))
	{
		reply(fd, ERR_NOSUCHCHANNEL, name + " :No such channel");
		return;
	}
	Channel *channel = findChannel(name);
	if (channel == NULL)
	{
		channels[name] = Channel(name);
		channel = &channels[name];
		channel->operators.insert(fd);	// whoever creates a channel is its first operator
	}
	else if (channel->isMember(fd) || !canJoin(fd, *channel, key))
		return;

	channel->members.insert(fd);
	channel->invited.erase(fd);	// an invitation can only be used once

	sendToChannel(*channel, ":" + clients[fd].prefix() + " JOIN " + name);
	if (!channel->topic.empty())
		reply(fd, RPL_TOPIC, name + " :" + channel->topic);
	reply(fd, RPL_NAMREPLY, "= " + name + " :" + memberList(*channel));
	reply(fd, RPL_ENDOFNAMES, name + " :End of /NAMES list");
}

// Checks the channel modes. Sends the error and returns false if the user may not join.
bool Server::canJoin(int fd, const Channel &channel, const std::string &key)
{
	if (channel.isInvited(fd))	// an invitation lets the user in, whatever the modes are
		return true;
	if (channel.inviteOnly)
		reply(fd, ERR_INVITEONLYCHAN, channel.name + " :Cannot join channel (+i)");
	else if (!channel.key.empty() && key != channel.key)
		reply(fd, ERR_BADCHANNELKEY, channel.name + " :Cannot join channel (+k)");
	else if (channel.userLimit != 0 && channel.members.size() >= channel.userLimit)
		reply(fd, ERR_CHANNELISFULL, channel.name + " :Cannot join channel (+l)");
	else
		return true;
	return false;
}
