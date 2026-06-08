/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 10:39:14 by skuor             #+#    #+#             */
/*   Updated: 2026/06/08 14:02:52 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec/cmdExec.hpp"

void	CmdExec::kick(t_cmdParser & cmd, Client *c)
{
	if (cmd.params.size() < 2)
		return (sendMsg(ERR_461, c, "KICK"));

	Channel *chan = this->_srv->getChannelByName(cmd.params[0]);
	if (chan == NULL)
		return (sendMsg(ERR_403, c, "", chan));

	if (!chan->isMember(c))
		return (sendMsg(ERR_442, c, "", chan));

	if (!chan->isOpe(c))
		return (sendMsg(ERR_482, c, "", chan));
	
		//de base : 	std::vector<std::string> users = parsingParams(cmd.params[1]);

	std::vector<std::string> users = parsingParam(cmd.params[1]);
	std::vector<std::string>::iterator	it;

	for (it = users.begin(); it != users.end(); it++)
	{
		Client *dest = this->_srv->getClientByNick(*it);
		
		std::string reason = cmd.trailing.empty() ? "You have been kicked" : cmd.trailing;
		std::string prefix = prefixStr(c);
		std::string msg = prefix + " KICK " + cmd.params[0] + " " + *it + " :" + reason;
			
		if (!dest || !chan->isMember(dest))
			sendMsg(ERR_441, c, *it, chan);
		else
		{
			sendToAll(msg, *chan);
			chan->removeMember(dest);
			chan->removeOpe(dest);
			
		}
	}
	if (chan->getMembers().empty())
		this->_srv->delChannel(chan->getName());
}