/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:09:02 by agouin            #+#    #+#             */
/*   Updated: 2026/05/27 17:53:47 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/base.hpp"
#include <arpa/inet.h>


Server::Server(std::string port, std::string password) : _port(port), _password(password)
{
	this->_server_socket_fd = socket(AF_INET, SOCK_STREAM, 0); //protocole par defaut
	if (_server_socket_fd < 0)
		return ;//on va faire un throw
	this->addr.sin_family = AF_INET; //bien IPV4
	this->addr.sin_port = htons(8080);
//	inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr); 
//PAS LE DROIT DUTILISER CETTE FONCTION	//je peux utiliser inet_ntop
	//inet_ntop();
	//sinon je lecris de facon dur 
	this->addr.sin_addr = INADDR_ANY;// a voir

	if (bind(_server_socket_fd, (sockaddr*)&addr, sizeof(addr)) < 0)
		return ;//mais trow
	if (listen(_server_socket_fd, SOMAXCONN) < 0)//deveint socket passif = serveur = accepter les demandes de connexions
		return ;//mais trow

	//soit je prends select ou poll
}


Server::Server(const Server& src)
{
	*this = src;
}
	

Server &Server::operator=(const Server& src)
{
	if (this != &src)
	{

	}
	return (*this);
}


Server::~Server()
{
}


void Server::write(std::string msg)//voir si je donne un nom au server
{
	std::cout << GREEN << "Server : " << DEFAULT << msg << std::endl;	
}