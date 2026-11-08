#include "../inc/Server.hpp"

// Runs one line received from a client, e.g. "JOIN #general".
void Server::executeLine(int fd, const std::string &line)
{
	Args args = splitMessage(line);
	if (args.empty())
		return;
	std::string command = toUpper(args[0]);
	args.erase(args.begin());

	if (command == "CAP" || command == "PONG")
		return;	// capability negotiation is not supported, and PONG needs no answer

	// Commands allowed before registration
	if (command == "PASS")
		cmdPass(fd, args);
	else if (command == "NICK")
		cmdNick(fd, args);
	else if (command == "USER")
		cmdUser(fd, args);
	else if (command == "PING")
		cmdPing(fd, args);
	else if (command == "QUIT")
		cmdQuit(fd, args);
	// Every other command needs a registered client
	else if (!clients[fd].registered)
		reply(fd, ERR_NOTREGISTERED, ":You have not registered");
	else if (command == "JOIN")
		cmdJoin(fd, args);
	else if (command == "PART")
		cmdPart(fd, args);
	else if (command == "PRIVMSG")
		cmdPrivmsg(fd, args, false);
	else if (command == "NOTICE")
		cmdPrivmsg(fd, args, true);
	else if (command == "WHO")
		cmdWho(fd, args);
	else if (command == "KICK")
		cmdKick(fd, args);
	else if (command == "INVITE")
		cmdInvite(fd, args);
	else if (command == "TOPIC")
		cmdTopic(fd, args);
	else if (command == "MODE")
		cmdMode(fd, args);
	else
		reply(fd, ERR_UNKNOWNCOMMAND, command + " :Unknown command");
}

// Queues a message for a client. It is really sent by writeToClient(),
// once poll() says that the socket is writable.
void Server::sendTo(int fd, const std::string &message)
{
	std::map<int, Client>::iterator it = clients.find(fd);
	if (it != clients.end())
		it->second.outBuffer += message + "\r\n";
}

// Numeric reply, e.g. ":ircserv 461 alice JOIN :Not enough parameters"
void Server::reply(int fd, const std::string &code, const std::string &text)
{
	std::string nickname = clients[fd].nickname.empty() ? "*" : clients[fd].nickname;
	sendTo(fd, ":" SERVER_NAME " " + code + " " + nickname + " " + text);
}

void Server::sendToChannel(const Channel &channel, const std::string &message, int exceptFd)
{
	for (std::set<int>::const_iterator it = channel.members.begin(); it != channel.members.end(); ++it)
		if (*it != exceptFd)
			sendTo(*it, message);
}

// Sends a message once to every user who shares at least one channel with `fd`.
void Server::sendToPeers(int fd, const std::string &message)
{
	std::set<int> peers;
	for (std::map<std::string, Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
		if (it->second.isMember(fd))
			peers.insert(it->second.members.begin(), it->second.members.end());
	peers.erase(fd);
	for (std::set<int>::iterator it = peers.begin(); it != peers.end(); ++it)
		sendTo(*it, message);
}

// Called after PASS, NICK and USER: once all three are done, welcome the user.
void Server::tryToRegister(int fd)
{
	Client &client = clients[fd];
	if (client.registered || !client.passwordOk || client.nickname.empty() || client.username.empty())
		return;
	client.registered = true;
	reply(fd, RPL_WELCOME, ":Welcome to the ft_irc network " + client.prefix());
	reply(fd, RPL_YOURHOST, ":Your host is " SERVER_NAME ", running version 1.0");
	reply(fd, RPL_CREATED, ":This server was created for the 42 ft_irc project");
	reply(fd, RPL_MYINFO, SERVER_NAME " 1.0 o itkol");
	reply(fd, ERR_NOMOTD, ":MOTD File is missing");
}

Client *Server::findClient(const std::string &nickname)
{
	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); ++it)
		if (it->second.nickname == nickname)
			return &it->second;
	return NULL;
}

Channel *Server::findChannel(const std::string &name)
{
	std::map<std::string, Channel>::iterator it = channels.find(name);
	if (it == channels.end())
		return NULL;
	return &it->second;
}

// Removes a user from a channel. A channel with no members left is deleted,
// so a Channel pointer must not be used after calling this.
void Server::removeFromChannel(const std::string &name, int fd)
{
	std::map<std::string, Channel>::iterator it = channels.find(name);
	if (it == channels.end())
		return;
	it->second.removeMember(fd);
	if (it->second.members.empty())
		channels.erase(it);
}

// "@alice bob carol": the member nicknames, operators prefixed with '@'
std::string Server::memberList(const Channel &channel)
{
	std::string list;
	for (std::set<int>::const_iterator it = channel.members.begin(); it != channel.members.end(); ++it)
	{
		if (!list.empty())
			list += " ";
		if (channel.isOperator(*it))
			list += "@";
		list += clients[*it].nickname;
	}
	return list;
}
