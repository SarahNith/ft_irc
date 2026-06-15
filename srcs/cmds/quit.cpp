/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 14:59:54 by skuor             #+#    #+#             */
/*   Updated: 2026/06/15 17:05:55 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec/cmdExec.hpp"

void	CmdExec::quit(t_cmdParser & cmd, Client *c)
{
	std::map<std::string, Channel> &chansList = this->_srv->getChannels(); //liste des chans sur le serveur
	std::map<std::string, Channel>::iterator it1;
	
	std::string prefix = prefixStr(c);
	std::string	reason = cmd.trailing.empty() ? "" : cmd.trailing;
	
	for (it1 = chansList.begin(); it1 != chansList.end(); it1++)
	{
		if (it1->second.isMember(c))
		{
			c->write("quit the server");
			std::string msg = prefix + " QUIT :Quit: " + reason;
			sendToAllExcept(msg, it1->second, c);
			it1->second.removeMember(c);
			it1->second.removeOpe(c);
		}
	}
	sendMsg("ERROR :Closing connection", c);
	this->_srv->delClient(c->getClientFd());
}
