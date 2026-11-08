#include "../inc/Server.hpp"

// TOPIC <#channel>             shows the topic
// TOPIC <#channel> :<topic>    changes it (only operators when the channel is +t)
void Server::cmdTopic(int fd, const Args &args)
{
	if (args.empty())
	{
		reply(fd, ERR_NEEDMOREPARAMS, "TOPIC :Not enough parameters");
		return;
	}
	Channel *channel = findChannel(args[0]);

	if (channel == NULL)
		reply(fd, ERR_NOSUCHCHANNEL, args[0] + " :No such channel");
	else if (!channel->isMember(fd))
		reply(fd, ERR_NOTONCHANNEL, args[0] + " :You're not on that channel");
	else if (args.size() == 1 && channel->topic.empty())
		reply(fd, RPL_NOTOPIC, args[0] + " :No topic is set");
	else if (args.size() == 1)
		reply(fd, RPL_TOPIC, args[0] + " :" + channel->topic);
	else if (channel->topicLocked && !channel->isOperator(fd))
		reply(fd, ERR_CHANOPRIVSNEEDED, args[0] + " :You're not channel operator");
	else
	{
		channel->topic = args[1];
		sendToChannel(*channel, ":" + clients[fd].prefix() + " TOPIC " + args[0] + " :" + args[1]);
	}
}
