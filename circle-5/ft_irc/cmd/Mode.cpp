#include "../inc/Server.hpp"
#include <cstdlib>

// MODE <#channel> [<modes> [<parameters>...]]     e.g. MODE #42 +kl-i secret 10
//   i         invite-only channel
//   t         only operators can change the topic
//   k <key>   channel password
//   o <nick>  give / take operator rights
//   l <max>   user limit
void Server::cmdMode(int fd, const Args &args)
{
	if (args.empty())
	{
		reply(fd, ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
		return;
	}
	if (args[0].empty() || args[0][0] != '#')	// user modes: not supported, but clients send "MODE nick +i"
	{
		if (args[0] == clients[fd].nickname)
			reply(fd, RPL_UMODEIS, "+");
		else
			reply(fd, ERR_USERSDONTMATCH, ":Can't change mode for other users");
		return;
	}
	Channel *channel = findChannel(args[0]);

	if (channel == NULL)
		reply(fd, ERR_NOSUCHCHANNEL, args[0] + " :No such channel");
	else if (!channel->isMember(fd))
		reply(fd, ERR_NOTONCHANNEL, args[0] + " :You're not on that channel");
	else if (args.size() == 1)
		reply(fd, RPL_CHANNELMODEIS, args[0] + " " + channel->modeString());
	else if (args[1] == "b" || args[1] == "+b")	// ban list asked by clients after JOIN: we have no bans
		reply(fd, RPL_ENDOFBANLIST, args[0] + " :End of channel ban list");
	else if (!channel->isOperator(fd))
		reply(fd, ERR_CHANOPRIVSNEEDED, args[0] + " :You're not channel operator");
	else
		changeModes(fd, *channel, args);
}

// Applies each mode letter of args[1], then tells the channel what really changed.
void Server::changeModes(int fd, Channel &channel, const Args &args)
{
	const std::string	&modes = args[1];
	size_t				next = 2;		// args[next] is the next unused mode parameter
	bool				adding = true;
	char				lastSign = 0;
	std::string			changes;		// what really changed, e.g. "+kl-i"
	std::string			changeParams;	// their parameters, e.g. " secret 10"

	for (size_t i = 0; i < modes.size(); i++)
	{
		char		mode = modes[i];
		std::string	param;

		if (mode == '+' || mode == '-')
		{
			adding = (mode == '+');
			continue;
		}
		if (mode == 'o' || (adding && (mode == 'k' || mode == 'l')))	// these need a parameter
		{
			if (next >= args.size())
			{
				reply(fd, ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
				continue;
			}
			param = args[next++];
		}
		else if (mode == 'k' && next < args.size())
			next++;		// "-k <key>": the key is not needed, skip it

		if (!applyMode(fd, channel, mode, adding, param))
			continue;	// nothing changed, or an error was already sent

		char sign = adding ? '+' : '-';
		if (sign != lastSign)
			changes += sign;
		lastSign = sign;
		changes += mode;
		if (!param.empty())
			changeParams += " " + param;
	}
	if (!changes.empty())
		sendToChannel(channel, ":" + clients[fd].prefix() + " MODE " + channel.name + " " + changes + changeParams);
}

// Changes one mode of the channel. Returns true if something really changed.
bool Server::applyMode(int fd, Channel &channel, char mode, bool adding, const std::string &param)
{
	if (mode == 'i')
	{
		if (channel.inviteOnly == adding)
			return false;
		channel.inviteOnly = adding;
	}
	else if (mode == 't')
	{
		if (channel.topicLocked == adding)
			return false;
		channel.topicLocked = adding;
	}
	else if (mode == 'k' && !adding)
	{
		if (channel.key.empty())
			return false;
		channel.key = "";
	}
	else if (mode == 'k')
	{
		if (param.empty() || param.find_first_of(" ,") != std::string::npos)
		{
			reply(fd, ERR_INVALIDMODEPARAM, channel.name + " k " + param + " :Invalid key");
			return false;
		}
		channel.key = param;
	}
	else if (mode == 'l' && !adding)
	{
		if (channel.userLimit == 0)
			return false;
		channel.userLimit = 0;
	}
	else if (mode == 'l')
	{
		if (param.empty() || param.size() > 6 || param.find_first_not_of("0123456789") != std::string::npos
			|| std::atoi(param.c_str()) == 0)
		{
			reply(fd, ERR_INVALIDMODEPARAM, channel.name + " l " + param + " :Invalid limit");
			return false;
		}
		channel.userLimit = std::atoi(param.c_str());
	}
	else if (mode == 'o')
	{
		Client *target = findClient(param);
		if (target == NULL || !channel.isMember(target->fd))
		{
			reply(fd, ERR_USERNOTINCHANNEL, param + " " + channel.name + " :They aren't on that channel");
			return false;
		}
		if (channel.isOperator(target->fd) == adding)
			return false;
		if (adding)
			channel.operators.insert(target->fd);
		else
			channel.operators.erase(target->fd);
	}
	else
	{
		reply(fd, ERR_UNKNOWNMODE, std::string(1, mode) + " :is unknown mode char to me");
		return false;
	}
	return true;
}
