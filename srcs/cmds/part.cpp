/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 16:09:23 by skuor             #+#    #+#             */
/*   Updated: 2026/06/09 10:00:57 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec/cmdExec.hpp"

void	CmdExec::part(t_cmdParser & cmd, Client *c)
{
	if (cmd.params.size() < 1)
		return (sendMsg(ERR_461, c, "PART"));
	
	std::vector<std::string> chansVec = parsingParam(cmd.params[0]);
	std::vector<std::string>::iterator	it;

	for (it = chansVec.begin(); it != chansVec.end(); it++)
	{
		Channel *chan = this->_srv->getChannelByName(*it);
		if (!chan)
		{
			sendMsg(ERR_403, c, "", chan);
			continue ;
		}

		if (!chan->isMember(c))
		{
			sendMsg(ERR_442, c, "", chan);
			continue ;
		}
			
		std::string reason = cmd.trailing.empty() ? "" : cmd.trailing;
		std::string prefix = prefixStr(c);
		std::string msg = prefix + " PART " + *it  + " :" + reason;
		
		sendToAll(msg, *chan);
		chan->removeMember(c);
		chan->removeOpe(c);
		if (chan->getMembers().empty())
		{
			chan->write("Channel closed");
			this->_srv->delChannel(chan->getName());
		}
	}	
}
