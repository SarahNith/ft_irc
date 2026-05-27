#ifndef SERVER_HPP
# define SERVER_HPP

#include <string>
#include <fstream>
#include <iostream>
//#include "../includes/colors.hpp"


class	Server 
{
	public :

		Server(std::string port, std::string password);
		Server(const Server &src);
		Server &operator=(const Server &src);
		~Server();

	private :

		std::string	_port;
		std::string _password;
	
};

#endif