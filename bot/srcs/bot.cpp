/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:12:19 by skuor             #+#    #+#             */
/*   Updated: 2026/06/12 17:03:18 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bot.hpp"

void	Bot::sendMsg(std::string msg)
{
	std::string	newMsg = msg;

	newMsg += "\r\n";
	size_t	fullSize = newMsg.size();
	size_t	sent = 0;
	
	while (sent < fullSize)
	{
		ssize_t n = send(_fd, newMsg.c_str() + sent, fullSize - sent, 0);
		if (n == -1)
			throw Exception("Error: send failed");
		sent += n;
	}
}

void	Bot::registerBot()
{
	std::string passMsg = "PASS " + _password;
	std::string	nickMsg = "NICK BotCensor";
	std::string userMsg = "USER Bot 0 * :Bot Censor";

	_write("Sending PASS, NICK and USER");
	sendMsg(passMsg);
	sendMsg(nickMsg);
	sendMsg(userMsg);
}

void	Bot::handleLine(std::string line)
{
	std::string pingRep;
	size_t	findPing = line.find("PING");
	if (findPing != std::string::npos)
	{
		pingRep = line.substr(findPing + 5);
		std::string pingMsg = "PONG " + pingRep;
		sendMsg(pingMsg);
	}
}


void	Bot::_write(std::string msg)
{
	std::cout << YELLOW << "Bot : " << DEFAULT << msg << std::endl;
}