/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:16:42 by skuor             #+#    #+#             */
/*   Updated: 2026/06/10 18:50:09 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec.hpp"

void	CmdExec::sendMsg(std::string msg, Client *c, std::string other, Channel *ch)
{
	std::string	newMsg = msg;
	
	newMsg = replaceAll(msg, "<client>", c->getNickName());
	newMsg = replaceAll(newMsg, "<command>", other);
	if (ch != NULL)
	{
		newMsg = replaceAll(newMsg, "<channel>", ch->getName());
		newMsg = replaceAll(newMsg, "<topic>", ch->getTopic());
	}
	if (other.empty())
		newMsg = replaceAll(newMsg, "<nick>", c->getNickName());
	else
	{
		newMsg = replaceAll(newMsg, "<nick>", other);
		newMsg = replaceAll(newMsg, "<channel>", other);
		newMsg = replaceAll(newMsg, "<datetime>", other);
		
	}
	newMsg = replaceAll(newMsg, "<user>", c->getUserName());
	newMsg = replaceAll(newMsg, "<host>", c->getHostname());
	
	std::string fullMsg = newMsg + "\r\n";
	size_t	fullSize = fullMsg.size();
	size_t	sent = 0;
	
	while (sent < fullSize)
	{
		// std::cout << c->getClientFd() << std::endl; 
		ssize_t n = send(c->getClientFd(), fullMsg.c_str() + sent, fullSize - sent, 0);
		// std::cout << "n = " << n << std::endl;
		if (n == -1)
		{
			write("Error: send failed");
			return ;
		}	
		sent += n;
	}
}

void		CmdExec::sendToAll(std::string msg, Channel &ch)
{
	std::vector<Client*> members = ch.getMembers();
	
	std::vector<Client*>::iterator it;
	std::vector<Client*>::iterator ite = members.end();
	
	for (it = members.begin(); it != ite; it++)
		sendMsg(msg, *it, "", &ch);
}

void		CmdExec::sendToAllExcept(std::string msg, Channel &ch, Client *Except)
{
	std::vector<Client*> members = ch.getMembers();
	
	std::vector<Client*>::iterator it;
	std::vector<Client*>::iterator ite = members.end();
	
	for (it = members.begin(); it != ite; it++)
	{
		if (*it != Except)
			sendMsg(msg, *it, "", &ch);
	}
}

std::string	CmdExec::prefixStr(Client *c)
{
	std::string prefix = ":" + c->getNickName() + "!" + c->getUserName() + "@" + c->getHostname();

	return prefix;
}

std::string	CmdExec::replaceAll(std::string str, std::string toReplace, std::string strReplace)
{
	std::string	newStr;
	size_t	i = 0;
	while (i < str.length())
	{
		if (toReplace == "")
			return str;
		if (str.compare(i, toReplace.length(), toReplace) == 0)
		{
			newStr += strReplace;
			i += toReplace.length();
		}
		else
		{
			newStr += str[i];
			i++;
		}
	}
	return (newStr);
}