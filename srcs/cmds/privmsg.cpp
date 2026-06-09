/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 17:32:09 by skuor             #+#    #+#             */
/*   Updated: 2026/06/09 18:25:45 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec/cmdExec.hpp"

void	CmdExec::privmsg(t_cmdParser & cmd, Client *c)
{
	if (!checkRegistration(c))
		return ;
	
	if (cmd.params.size() < 1)
		return (sendMsg(ERR_411, c, "PRIVMSG"));

	if (cmd.trailing.empty())
		return (sendMsg(ERR_412, c));

	std::string prefix = prefixStr(c);
	std::string msg = prefix + " PRIVMSG " + cmd.params[0] + " :" + cmd.trailing;
		
	// std::cout << "nb de param: " << cmd.params.size() << std:: endl 
	// 	<< "cmd.param[0] = " << cmd.params[0] << std::endl
	// 	<< "trailing : " << cmd.trailing << std::endl;
 	if (cmd.params[0][0] == '#')
	{
		Channel *chan = this->_srv->getChannelByName(cmd.params[0]);
		if (!chan)
			return (sendMsg(ERR_403, c, cmd.params[0]));

		if (!chan->isMember(c))
			return (sendMsg(ERR_404, c, "", chan));
		
		c->write("sent a msg to the chan " + chan->getName());
		sendToAllExcept(msg, *chan, c);
	}
	else
	{
		Client *dest = this->_srv->getClientByNick(cmd.params[0]);
		if (!dest)
			return (sendMsg(ERR_401, c, cmd.params[0]));
		c->write("sent a private message to " + dest->getNickName());
		sendMsg(msg, dest);
	}
}
