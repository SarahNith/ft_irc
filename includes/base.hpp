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

#endif