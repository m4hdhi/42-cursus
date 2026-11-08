#include "../inc/Utils.hpp"
#include <cctype>
#include <cstdlib>
#include <sstream>

// Splits one IRC line into words. A word starting with ':' is the last one
// and keeps its spaces:
//   "PRIVMSG #room :hello world"  ->  ["PRIVMSG", "#room", "hello world"]
Args splitMessage(const std::string &line)
{
	Args	args;
	size_t	i = 0;

	if (!line.empty() && line[0] == ':')	// optional ":prefix" sent by some clients: skip it
		i = line.find(' ');
	while (i < line.size())
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == ':')
		{
			args.push_back(line.substr(i + 1));
			break;
		}
		else
		{
			size_t end = line.find(' ', i);
			if (end == std::string::npos)
				end = line.size();
			args.push_back(line.substr(i, end - i));
			i = end;
		}
	}
	return args;
}

// "#a,#b,,#c"  ->  ["#a", "#b", "#c"]
Args splitList(const std::string &list)
{
	Args				items;
	std::string			item;
	std::istringstream	stream(list);

	while (std::getline(stream, item, ','))
		if (!item.empty())
			items.push_back(item);
	return items;
}

std::string toUpper(std::string text)
{
	for (size_t i = 0; i < text.size(); i++)
		text[i] = std::toupper(static_cast<unsigned char>(text[i]));
	return text;
}

std::string toString(size_t number)
{
	std::ostringstream stream;
	stream << number;
	return stream.str();
}

// Accepts "1" to "65535" only.
bool parsePort(const std::string &text, int &port)
{
	if (text.empty() || text.size() > 5 || text.find_first_not_of("0123456789") != std::string::npos)
		return false;
	port = std::atoi(text.c_str());
	return port >= 1 && port <= 65535;
}

// RFC 2812: a letter or one of []\`_^{|} first, then letters, digits, those signs or '-'.
bool isValidNickname(const std::string &nickname)
{
	const std::string special = "[]\\`_^{|}";

	if (nickname.empty() || nickname.size() > 30)
		return false;
	for (size_t i = 0; i < nickname.size(); i++)
	{
		unsigned char c = nickname[i];
		bool allowed = std::isalpha(c) || special.find(c) != std::string::npos
			|| (i > 0 && (std::isdigit(c) || c == '-'));
		if (!allowed)
			return false;
	}
	return true;
}

// '#' followed by 1 to 49 characters, without spaces, commas or colons.
bool isValidChannelName(const std::string &name)
{
	return name.size() >= 2 && name.size() <= 50 && name[0] == '#'
		&& name.find_first_of(" ,:") == std::string::npos;
}
