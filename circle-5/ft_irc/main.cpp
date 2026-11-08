#include "inc/Server.hpp"
#include <csignal>
#include <iostream>
#include <stdexcept>

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return 1;
	}
	int			port;
	std::string	password = argv[2];
	if (!parsePort(argv[1], port))
	{
		std::cerr << "Error: the port must be a number between 1 and 65535" << std::endl;
		return 1;
	}
	if (password.empty() || password.find_first_of(" \t\r\n") != std::string::npos)
	{
		std::cerr << "Error: the password must not be empty or contain spaces" << std::endl;
		return 1;
	}

	std::signal(SIGINT, Server::stop);		// ctrl+C stops the server cleanly
	std::signal(SIGQUIT, Server::stop);		// ctrl+\ too
	std::signal(SIGPIPE, SIG_IGN);			// writing to a closed socket must not kill the server

	try
	{
		Server server(port, password);
		server.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	std::cout << "Server stopped" << std::endl;
	return 0;
}
