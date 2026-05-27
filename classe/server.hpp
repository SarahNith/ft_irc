#ifndef SERVER_HPP
# define SERVER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//#include "../includes/colors.hpp"
#include "client.hpp"
#include <map>

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
		//voir si util
		struct addrinfo	_hints;
		struct addrinfo*	_servinfo;
		int	_server_socket_fd;
		std::map<const int, Client>	_clients;
};

#endif