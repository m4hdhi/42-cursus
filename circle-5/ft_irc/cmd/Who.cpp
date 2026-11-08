#include "../inc/Server.hpp"

// WHO <#channel>: lists the members of a channel.
// Not required by the subject, but IRC clients send it right after JOIN.
void Server::cmdWho(int fd, const Args &args)
{
	std::string	mask = args.empty() ? "*" : args[0];
	Channel		*channel = findChannel(mask);

	if (channel != NULL)
	{
		for (std::set<int>::iterator it = channel->members.begin(); it != channel->members.end(); ++it)
		{
			Client		&member = clients[*it];
			std::string	flags = channel->isOperator(*it) ? "H@" : "H";
			reply(fd, RPL_WHOREPLY, mask + " " + member.username + " " + member.ip + " " SERVER_NAME " "
				+ member.nickname + " " + flags + " :0 " + member.realname);
		}
	}
	reply(fd, RPL_ENDOFWHO, mask + " :End of WHO list");
}
