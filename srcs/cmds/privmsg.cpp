/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 17:32:09 by skuor             #+#    #+#             */
/*   Updated: 2026/06/04 18:30:14 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec.hpp"

void	CmdExec::privmsg(t_cmdParser & cmd, Client *c)
{
	if (!checkRegistration(c))
		return ;
	
	if (cmd.params.size() < 1)
		return (sendMsg(ERR_411, c, "PRIVMSG"));

	if (cmd.trailing.empty())
		return (sendMsg(ERR_412, c));

	std::string msg = ":" + c->getNickName() + "!" + c->getUserName() + "@" + c->getHostname()
		+ " PRIVMSG " + cmd.params[0] + " :" + cmd.trailing;
		
	if (cmd.params[0][0] == '#')
	{
		Channel *chan = this->_srv->getChannelByName(cmd.params[0]);
		if (chan == NULL)
			return (sendMsg(ERR_403, c, "", chan));

		if (!chan->isMember(c))
			return (sendMsg(ERR_404, c, "", chan));
		
		sendToAllExcept(msg, *chan, c);
	}
	else
	{
		Client *dest = this->_srv->getClientByNick(cmd.params[0]);
		if (!dest)
			return (sendMsg(ERR_401, c));
		sendMsg(msg, dest);
	}
}
