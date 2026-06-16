/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   botServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:12:51 by skuor             #+#    #+#             */
/*   Updated: 2026/06/16 10:26:21 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bot.hpp"

bool Bot::_signal = false;

void	Bot::connectToServer()
{
	sockaddr_in addr;
	
	this->_fd = socket(AF_INET, SOCK_STREAM, 0); //protocole par defaut
	if (this->_fd < 0)
		throw Exception("Error : Socket creation failed");
	addr.sin_family = AF_INET; //bien IPV4
	addr.sin_port = htons(_port);

	if ((addr.sin_addr.s_addr = inet_addr(_ip.c_str())) == INADDR_NONE)
		throw Exception("Error : Invalid IP address");
		
	if (connect(this->_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		throw Exception("Error : Connection failed");
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	setsockopt(_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
}

void	Bot::recvLoop()
{
	char buffer[1024];
	ssize_t	buf;

	buf = recv(_fd, buffer, sizeof(buffer) - 1, 0);
	if(buf == 0)
		return ;
	if (buf < 0)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return;  // timeout normal, pas une erreur
		std::cerr << RED << "Error : Recv failed" << DEFAULT << std::endl;
		return;
	}
	buffer[buf] = '\0';

	_readBuf += buffer;

	size_t i = 0;

	while((i = _readBuf.find("\r\n")) != std::string::npos)
	{
		std::string line = _readBuf.substr(0, i);
		_readBuf.erase(0, i + 2);
		if (!line.empty())
			handleLine(line);
	}	
}

void	Bot::run()
{
	signal(SIGINT, _signalhander);
	signal(SIGQUIT, _signalhander);
	
	connectToServer();
	registerBot();
	while (Bot::_signal != true)
		recvLoop();
}

void	Bot::_signalhander(int num)
{
	(void)num;
	Bot::_signal = true;
	std::cout << std::endl << RED << "Signal detected" << DEFAULT << std::endl;
}
