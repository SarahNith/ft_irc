#ifndef SERVER_HPP
# define SERVER_HPP

#include "../includes/base.hpp"


class	Server 
{
	public :

		Server(int port, std::string password);
		~Server();

		void	write(std::string msg);

		//voit fonction

		void	startServer();
		void	addClient();
		void	delClient();

		void	addChannel();
		void	AddCienttoChannel();

		
		void	run_server();


	private :

		int	_port;
		std::string _password;
		int	_server_socket_fd;
		sockaddr_in addr;
		std::vector<pollfd> _listfd;

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