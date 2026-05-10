/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 02:01:32 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/05/11 02:06:13 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <string>

static std::string replaceAll(std::string content, std::string s1, std::string s2)
{
	std::string result;
	std::size_t pos;
	std::size_t start;

	start = 0;
	pos = content.find(s1, start);
	while (pos != std::string::npos)
	{
		result += content.substr(start, pos - start);
		result += s2;
		start = pos + s1.length();
		pos = content.find(s1, start);
	}
	result += content.substr(start);
	return (result);
}

static int readFile(std::string filename, std::string &content)
{
	std::ifstream input;
	std::string line;

	input.open(filename.c_str());
	if (!input.is_open())
	{
		std::cerr << "Error: cannot open input file" << std::endl;
		return (1);
	}
	while (std::getline(input, line))
	{
		content += line;
		if (!input.eof())
			content += "\n";
	}
	if (input.bad())
	{
		std::cerr << "Error: cannot read input file" << std::endl;
		input.close();
		return (1);
	}
	input.close();
	return (0);
}

static int writeFile(std::string filename, std::string content)
{
	std::ofstream output;

	output.open((filename + ".replace").c_str());
	if (!output.is_open())
	{
		std::cerr << "Error: cannot create output file" << std::endl;
		return (1);
	}
	output << content;
	if (output.fail())
	{
		std::cerr << "Error: cannot write output file" << std::endl;
		output.close();
		return (1);
	}
	output.close();
	return (0);
}

int main(int argc, char **argv)
{
	std::string filename;
	std::string content;

	if (argc != 4)
	{
		std::cerr << "Usage: ./Sed_is_for_losers <filename> <s1> <s2>" << std::endl;
		return (1);
	}
	filename = argv[1];
	if (filename.empty() || std::string(argv[2]).empty())
	{
		std::cerr << "Error: filename and s1 cannot be empty" << std::endl;
		return (1);
	}
	if (readFile(filename, content))
		return (1);
	if (writeFile(filename, replaceAll(content, argv[2], argv[3])))
		return (1);
	return (0);
}
