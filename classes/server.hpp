#ifndef SERVER_HPP
# define SERVER_HPP

#include "../includes/base.hpp"


class	Server 
{
	public :

		Server(std::string port, std::string password);
		Server(const Server &src);
		Server &operator=(const Server &src);
		~Server();

		void	write(std::string msg);

		//voit fonction

		void	startServer();
		void	addClient();
		void	delClient();

		void	addChannel();
		void	AddCienttoChannel();


	private :

		std::string	_port;
		std::string _password;
		int	_server_socket_fd;
		sockaddr_in addr; //voir ce que cest exactement

		//voir si util
		//struct addrinfo	_hints;
		//struct addrinfo*	_servinfo;
		//std::map<const int, Client>	_clients;
		//std::map<std::string, Channel>	_channels;
		//std::string	_datetime;
		//std::vector<server_op>	_irc_operators;
		//std::string	_motd;
};

#endif