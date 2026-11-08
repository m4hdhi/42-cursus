#ifndef SERVER_HPP
#define SERVER_HPP

#include <csignal>
#include <map>
#include <string>
#include "Channel.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Utils.hpp"

class Server
{
public:
	Server(int serverPort, const std::string &serverPassword);
	~Server();

	void		run();
	static void	stop(int signal);

private:
	Server(const Server &);				// not copyable: the server owns its sockets
	Server &operator=(const Server &);

	// src/Server.cpp: sockets and the poll() loop
	void	createListeningSocket();
	void	acceptClient();
	void	readFromClient(int fd);
	void	writeToClient(int fd);
	void	leaveAllChannels(int fd, const std::string &reason);
	void	disconnectClient(int fd, const std::string &reason);

	// src/Messages.cpp: running commands, sending messages, finding users and channels
	void		executeLine(int fd, const std::string &line);
	void		sendTo(int fd, const std::string &message);
	void		reply(int fd, const std::string &code, const std::string &text);
	void		sendToChannel(const Channel &channel, const std::string &message, int exceptFd = -1);
	void		sendToPeers(int fd, const std::string &message);
	void		tryToRegister(int fd);
	Client		*findClient(const std::string &nickname);
	Channel		*findChannel(const std::string &name);
	void		removeFromChannel(const std::string &name, int fd);
	std::string	memberList(const Channel &channel);

	// cmd/*.cpp: one file per command
	void	cmdPass(int fd, const Args &args);
	void	cmdNick(int fd, const Args &args);
	void	cmdUser(int fd, const Args &args);
	void	cmdPing(int fd, const Args &args);
	void	cmdQuit(int fd, const Args &args);
	void	cmdJoin(int fd, const Args &args);
	void	joinChannel(int fd, const std::string &name, const std::string &key);
	bool	canJoin(int fd, const Channel &channel, const std::string &key);
	void	cmdPart(int fd, const Args &args);
	void	cmdPrivmsg(int fd, const Args &args, bool isNotice);
	void	cmdWho(int fd, const Args &args);
	void	cmdKick(int fd, const Args &args);
	void	cmdInvite(int fd, const Args &args);
	void	cmdTopic(int fd, const Args &args);
	void	cmdMode(int fd, const Args &args);
	void	changeModes(int fd, Channel &channel, const Args &args);
	bool	applyMode(int fd, Channel &channel, char mode, bool adding, const std::string &param);

	static volatile std::sig_atomic_t	stopRequested;	// set by SIGINT / SIGQUIT

	int								port;
	std::string						password;
	int								listenFd;
	std::map<int, Client>			clients;	// key: socket fd
	std::map<std::string, Channel>	channels;	// key: channel name, e.g. "#general"
};

#endif
