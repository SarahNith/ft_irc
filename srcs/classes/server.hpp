#ifndef SERVER_HPP
# define SERVER_HPP

#include "../../includes/base.hpp"


class	Server 
{
	public :

		Server(int port, std::string password);
		~Server();

		void	write(std::string msg);

		//voit fonction

		std::string getPassword() const;
		std::string	getDatetime() const;
		std::map<std::string, Channel>& getChannels();

		void	run_server();
		void	AddClient();
		void	delClient(int fd);

		void	addChannel();
		void	AddCienttoChannel();
		void	delChannel(std::string chanName);

		void	ClientData(int fd);

		Client*		getClientByNick(std::string nickname);
		Channel*	getChannelByName(std::string name);

		static void	signalhander(int num);

		std::string itos(int nb);
		

	private :

		int	_port;
		std::string _password;
		int	_server_socket_fd;
		sockaddr_in addr;
		std::vector<pollfd> _listfd;
		static bool _signal;
		std::map<const int, Client>	_clients;
		std::map<std::string, Channel>	_channels;
		std::string	_datetime;
		
};


#endif