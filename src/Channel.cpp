#include "../inc/Channel.hpp"
#include "../inc/Utils.hpp"

Channel::Channel() : userLimit(0), inviteOnly(false), topicLocked(false)
{
}

Channel::Channel(const std::string &channelName)
	: name(channelName), userLimit(0), inviteOnly(false), topicLocked(false)
{
}

bool Channel::isMember(int fd) const
{
	return members.count(fd) != 0;
}

bool Channel::isOperator(int fd) const
{
	return operators.count(fd) != 0;
}

bool Channel::isInvited(int fd) const
{
	return invited.count(fd) != 0;
}

void Channel::removeMember(int fd)
{
	members.erase(fd);
	operators.erase(fd);
	invited.erase(fd);
}

// The current modes as shown by "MODE #channel", e.g. "+itkl secret 10"
std::string Channel::modeString() const
{
	std::string modes = "+";
	std::string params;

	if (inviteOnly)
		modes += "i";
	if (topicLocked)
		modes += "t";
	if (!key.empty())
	{
		modes += "k";
		params += " " + key;
	}
	if (userLimit > 0)
	{
		modes += "l";
		params += " " + toString(userLimit);
	}
	return modes + params;
}
