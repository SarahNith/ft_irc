/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:09:02 by agouin            #+#    #+#             */
/*   Updated: 2026/05/26 12:25:43 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/base.hpp"


Server::Server(std::string port, std::string password) : _port(port), _password(password)
{
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