#include "../inc/Server.hpp"
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>

volatile std::sig_atomic_t Server::stopRequested = 0;

Server::Server(int serverPort, const std::string &serverPassword)
	: port(serverPort), password(serverPassword), listenFd(-1)
{
}

Server::~Server()
{
	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); ++it)
		close(it->first);
	if (listenFd != -1)
		close(listenFd);
}

void Server::stop(int signal)
{
	(void)signal;
	stopRequested = 1;
}

// Creates the non-blocking socket that waits for new connections on `port`.
void Server::createListeningSocket()
{
	listenFd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenFd == -1)
		throw std::runtime_error("socket() failed");

	int reuse = 1;	// lets us restart the server right away on the same port
	if (setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
		throw std::runtime_error("setsockopt() failed");
	if (fcntl(listenFd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("fcntl() failed");

	struct sockaddr_in address;
	std::memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);	// accept connections on every network interface
	address.sin_port = htons(port);
	if (bind(listenFd, (struct sockaddr *)&address, sizeof(address)) == -1)
		throw std::runtime_error("bind() failed: is the port already used?");
	if (listen(listenFd, SOMAXCONN) == -1)
		throw std::runtime_error("listen() failed");
}

// The main loop. accept(), recv() and send() are only called after the single
// poll() below said that the socket is ready, so the server never blocks.
void Server::run()
{
	createListeningSocket();
	std::cout << "Listening on port " << port << std::endl;

	while (!stopRequested)
	{
		// 1. List the sockets to watch. We always want to know when there is
		//    something to read, but we only ask for "writable" (POLLOUT) when
		//    something is waiting to be sent to that client.
		std::vector<struct pollfd> fds;
		struct pollfd entry;
		entry.fd = listenFd;
		entry.events = POLLIN;
		entry.revents = 0;
		fds.push_back(entry);
		for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); ++it)
		{
			entry.fd = it->first;
			entry.events = POLLIN;
			if (!it->second.outBuffer.empty())
				entry.events |= POLLOUT;
			fds.push_back(entry);
		}

		// 2. Sleep until at least one socket is ready (or a signal arrives).
		if (poll(&fds[0], fds.size(), -1) == -1)
		{
			if (stopRequested)
				break;
			throw std::runtime_error("poll() failed");
		}

		// 3. Handle every ready socket.
		for (size_t i = 0; i < fds.size(); i++)
		{
			int		fd = fds[i].fd;
			short	ready = fds[i].revents;

			if (fd == listenFd)
			{
				if (ready & POLLIN)
					acceptClient();
				continue;
			}
			// Send first: a client that sends commands and then closes its side
			// (like `nc` at the end of its input) must still get the replies.
			if (ready & POLLOUT)
				writeToClient(fd);
			if ((ready & (POLLIN | POLLHUP | POLLERR)) && clients.count(fd))	// it may be gone after QUIT
				readFromClient(fd);
		}
	}
}

void Server::acceptClient()
{
	struct sockaddr_in	address;
	socklen_t			length = sizeof(address);

	int fd = accept(listenFd, (struct sockaddr *)&address, &length);
	if (fd == -1)
		return;
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
	{
		close(fd);
		return;
	}
	clients[fd] = Client(fd, inet_ntoa(address.sin_addr));
	std::cout << "Client " << fd << " connected from " << clients[fd].ip << std::endl;
}

// Reads what the client sent and runs every complete line.
void Server::readFromClient(int fd)
{
	char	buffer[512];
	ssize_t	bytes = recv(fd, buffer, sizeof(buffer), 0);

	if (bytes <= 0)	// 0: the client closed the connection, -1: error
	{
		disconnectClient(fd, "Connection closed");
		return;
	}
	clients[fd].inBuffer.append(buffer, bytes);

	// A command ends with "\n" (or "\r\n"). Data can arrive in several pieces
	// ("com", "man", "d\n"): an incomplete line just waits in inBuffer.
	while (clients.count(fd) && !clients[fd].quitting)	// nothing is run after QUIT
	{
		Client	&client = clients[fd];
		size_t	end = client.inBuffer.find('\n');
		if (end == std::string::npos)
			break;
		std::string line = client.inBuffer.substr(0, end);
		client.inBuffer.erase(0, end + 1);
		if (client.lineTooLong)	// this was the end of a too long line: ignore it
		{
			client.lineTooLong = false;
			continue;
		}
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);
		executeLine(fd, line);	// may disconnect the client (QUIT)
	}

	// An IRC line is at most 512 bytes. If a client sends more without a newline,
	// refuse that line (up to its '\n') instead of letting the buffer grow forever.
	if (clients.count(fd) && clients[fd].inBuffer.size() > 512)
	{
		clients[fd].inBuffer.clear();
		if (!clients[fd].lineTooLong)
			reply(fd, ERR_INPUTTOOLONG, ":Input line was too long");
		clients[fd].lineTooLong = true;
	}
}

// Sends as much of the waiting output as the socket accepts right now.
void Server::writeToClient(int fd)
{
	std::string	&data = clients[fd].outBuffer;
	ssize_t		sent = send(fd, data.c_str(), data.size(), 0);

	if (sent <= 0)
	{
		disconnectClient(fd, "Connection lost");
		return;
	}
	data.erase(0, sent);	// keep what did not fit for the next POLLOUT
	if (data.empty() && clients[fd].quitting)	// everything was sent after QUIT: now we can close
		disconnectClient(fd, "Quit");
}

// Tells the other users that the client quits and removes it from every channel.
void Server::leaveAllChannels(int fd, const std::string &reason)
{
	sendToPeers(fd, ":" + clients[fd].prefix() + " QUIT :" + reason);

	std::vector<std::string> names;	// copy the names: removeFromChannel() may erase channels
	for (std::map<std::string, Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
		names.push_back(it->first);
	for (size_t i = 0; i < names.size(); i++)
		removeFromChannel(names[i], fd);	// also forgets invitations: the fd number will be reused
}

// Leaves every channel and closes the socket.
void Server::disconnectClient(int fd, const std::string &reason)
{
	leaveAllChannels(fd, reason);
	close(fd);
	clients.erase(fd);
	std::cout << "Client " << fd << " disconnected (" << reason << ")" << std::endl;
}
