#ifndef BASE_HPP
# define BASE_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

#include "colors.hpp"

#include "../classes/server.hpp"
#include "../classes/client.hpp"
#include "../classes/channel.hpp"
#include "../srcs/cmds/cmdExec.hpp"

//[:<prefix>] <command> [<parameters> [...]] [:<trailing>]
//ex: :dan!d@localhost PRIVMSG #chan :Hey what's up!
//ex: JOIN #channel,#channel2 key1,key2

typedef struct s_cmdParser
{
	std::string					prefix;
	std::string					command;
	std::vector<std::string>	params;
	std::string					trailing;

}						t_cmdParser;

void	test_parser();
#endif