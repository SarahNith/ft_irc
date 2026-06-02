/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:09:02 by agouin            #+#    #+#             */
/*   Updated: 2026/06/02 14:46:33 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/base.hpp"
#include <unistd.h>
#include <fcntl.h>

Server::Server(int port, std::string password) : _port(port), _password(password)
{
	this->_server_socket_fd = socket(AF_INET, SOCK_STREAM, 0); //protocole par defaut
	if (_server_socket_fd < 0)
		throw Exception("Error : Socket creation failed");
	this->addr.sin_family = AF_INET; //bien IPV4
	this->addr.sin_port = htons(port);
	this->addr.sin_addr.s_addr = htonl(INADDR_ANY);//permet d'écouter sur tout les interfaces
	//INADDR_ANY = 0 => écoute sur toutes les interfaces


	 int options = 1; //le premeir sur puisque sinon j'aurais eu un message comme "bind: Address already in use"
	// deuxième je sais pas 
	 if (setsockopt(this->_server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &options, sizeof(options)) == -1)
	 	throw(Exception("Error: server options could not be set"));
	 if (fcntl(this->_server_socket_fd, F_SETFL, O_NONBLOCK) == -1)
	 	throw(Exception("Error: server fcntl failed"));
	//"Ce socket (int) est maintenant responsable du port 8080."
	if (bind(_server_socket_fd, (sockaddr*)&addr, sizeof(addr)) < 0)
		throw Exception("Error : Bind failed");
	if (listen(_server_socket_fd, SOMAXCONN) < 0)//deveint socket passif = serveur = accepter les demandes de connexions
		throw Exception("Error : Listen failed");
	//SOMAXCONN = taille de la file d'attente pour les connexions


// 	struct pollfd
// {
//     int   fd;       // socket à surveiller
//     short events;   // événements qui nous intéressent
//     short revents;  // événements détectés par poll() = masque de bits
// };

	pollfd	serverFd;

	serverFd.fd = _server_socket_fd;
	serverFd.events = POLLIN;
	//POLLIN = prévenu si nouvelle connexions
	serverFd.revents = 0;
	this->_listfd.push_back(serverFd);
	//donc des quonn a une nouvelle connexion ou la mets dans le tableau de fd

}

Server::~Server()
{
	
}


void	Server::run_server()
{
	//je pense que cest pas mal de faire une boucle en fonction du signal ?????
	while(true) // = serveur
	{
		if(poll(&_listfd[0], _listfd.size(), -1) == -1)
			throw Exception("Error : Poll failed");
		for(size_t i = 0; i < _listfd.size(); i++)
		{
			if (_listfd[i].revents & POLLIN) //est ce que revents contient POLLIN en bits
			{
				if(_listfd[i].fd == _server_socket_fd)
					this->AddClient();
				else
					this->ClientData(_listfd[i].fd);
			}	
		}
	}
}


void	Server::AddClient()
{
	sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);
	int clientfd;

	clientfd = accept(_server_socket_fd, (sockaddr*)&client_addr, &len);
	if(clientfd == -1)
		throw Exception("Error : Accept failed");
	if (fcntl(clientfd, F_SETFL, O_NONBLOCK) == -1) //non bloquant
		throw(Exception("Error : Fnctl failed"));

	pollfd clientPoll;
	clientPoll.fd = clientfd;
	clientPoll.events = POLLIN;
	clientPoll.revents = 0;
	
	_listfd.push_back(clientPoll);

	Client newClient(clientfd);
	_clients[clientfd] = newClient;


	std::cout << YELLOW << "New connection : fd = " << DEFAULT << clientfd << std::endl;
}


void	Server::ClientData(int fd)
{
	char buffer[4096];
	ssize_t	buf;

	buf = recv(fd, buffer, sizeof(buffer) - 1, 0);
	if (buf <= 0)
	{
		if(buf == 0)
		{
			std::cout << MAGENTA << "Client disconnected" << DEFAULT << std::endl;
			//faut remove client
			return;
		}
		if(buf < 0)
		{
			std::cerr << RED << "Error : Recv failed" << DEFAULT << std::endl;
			return;
		}
	}
	buffer[buf] = '\0';
//std::cout << "Received : " << buffer << std::endl;
}


void Server::write(std::string msg)//voir si je donne un nom au server
{
	std::cout << GREEN << "Server : " << DEFAULT << msg << std::endl;	
}

