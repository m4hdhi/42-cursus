#include "../inc/Server.hpp"

// QUIT [:<reason>]: the client leaves the server.
// The socket is not closed here: replies may still be waiting in outBuffer
// (e.g. "PASS..NICK..USER..QUIT" sent at once). writeToClient() closes it
// once everything, including the ERROR line below, has been sent.
void Server::cmdQuit(int fd, const Args &args)
{
	std::string reason = "Quit";
	if (!args.empty())
		reason += ": " + args[0];

	leaveAllChannels(fd, reason);
	sendTo(fd, "ERROR :Closing link: " + clients[fd].ip + " (" + reason + ")");
	clients[fd].quitting = true;
}
