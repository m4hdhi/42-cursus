#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

// One connected user. The server keeps one Client per socket.
class Client
{
public:
	Client();
	Client(int clientFd, const std::string &clientIp);

	std::string prefix() const;	// "nick!user@ip": the source of the messages this client sends

	int			fd;
	std::string	ip;
	std::string	nickname;
	std::string	username;
	std::string	realname;
	bool		passwordOk;	// a correct PASS was received
	bool		registered;	// PASS, NICK and USER are done: every command can be used
	bool		quitting;	// QUIT received: the socket is closed once outBuffer is sent
	bool		lineTooLong;	// the current line is over 512 bytes: ignore it up to its '\n'
	std::string	inBuffer;	// received bytes that do not form a complete line yet
	std::string	outBuffer;	// bytes waiting for poll() to say that the socket is writable
};

#endif
