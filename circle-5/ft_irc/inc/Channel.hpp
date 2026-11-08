#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <set>
#include <string>

// A chat room. Users are stored by the fd of their socket.
class Channel
{
public:
	Channel();
	Channel(const std::string &channelName);

	bool		isMember(int fd) const;
	bool		isOperator(int fd) const;
	bool		isInvited(int fd) const;
	void		removeMember(int fd);
	std::string	modeString() const;

	std::string		name;
	std::string		topic;
	std::string		key;			// +k: password needed to join ("" = no password)
	size_t			userLimit;		// +l: maximum number of members (0 = no limit)
	bool			inviteOnly;		// +i: only invited users can join
	bool			topicLocked;	// +t: only operators can change the topic
	std::set<int>	members;
	std::set<int>	operators;		// members with operator rights (shown as @nick)
	std::set<int>	invited;		// users invited with INVITE who did not join yet
};

#endif
