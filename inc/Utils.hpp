#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

typedef std::vector<std::string> Args;

Args		splitMessage(const std::string &line);
Args		splitList(const std::string &list);
std::string	toUpper(std::string text);
std::string	toString(size_t number);
bool		parsePort(const std::string &text, int &port);
bool		isValidNickname(const std::string &nickname);
bool		isValidChannelName(const std::string &name);

#endif
