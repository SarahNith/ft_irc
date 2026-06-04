/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:16:42 by skuor             #+#    #+#             */
/*   Updated: 2026/06/04 18:21:58 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec.hpp"

void	CmdExec::sendMsg(std::string msg, Client *c, std::string other, Channel *ch)
{
	std::string	newMsg = msg;
	
	newMsg = replaceAll(msg, "<client>", c->getNickName());
	newMsg = replaceAll(newMsg, "<command>", other);
	if (other.empty())
		newMsg = replaceAll(newMsg, "<nick>", c->getNickName());
	else
		newMsg = replaceAll(newMsg, "<nick>", other);
	newMsg = replaceAll(newMsg, "<user>", c->getUserName());
	newMsg = replaceAll(newMsg, "<host>", c->getHostname());
	if (ch != NULL)
	{
		newMsg = replaceAll(newMsg, "<channel>", ch->getName());
		newMsg = replaceAll(newMsg, "<topic>", ch->getTopic());
	}
	
	std::string fullMsg = newMsg + "\r\n";
	send(c->getClientFd(), fullMsg.c_str(), fullMsg.size(), 0);
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