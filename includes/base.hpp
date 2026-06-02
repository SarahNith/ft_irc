#ifndef BASE_HPP
# define BASE_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>


//conteneur
#include <map>
#include <vector>
#include <vector>
#include <algorithm>

#include "colors.hpp"
#include "baseCmd.hpp"

#include <poll.h>






//class
#include "../srcs/classes/server.hpp"
#include "../srcs/classes/client.hpp"
#include "../srcs/classes/channel.hpp"



class Exception : public std::exception
{
	public:

		Exception(std::string msg) : str(msg)
		{

		}

		~Exception() throw() 
		{

		}

		

        const char* what() const throw()
		{
			return str.c_str();
		}

	private :
	
		std::string str;
};


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