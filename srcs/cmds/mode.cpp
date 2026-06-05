/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:54:37 by skuor             #+#    #+#             */
/*   Updated: 2026/06/05 18:49:32 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec/cmdExec.hpp"

static std::string	createChanModesStr(Channel *chan)
{
	std::string	chanModesStr = "+";
	std::string	args;
	
	if (!chan->getChannelKey().empty())
	{
		chanModesStr += 'k';
		args += " " + chan->getChannelKey();
	}
	if (chan->getCapacityLimit() != 0)
	{
		chanModesStr += 'l';
		std::stringstream	limitCapacity;
		limitCapacity << chan->getCapacityLimit();
		args += " " + limitCapacity.str();
	}
	if (chan->isInviteOnly())
		chanModesStr += 'i';
	if (chan->hasTopicRestriction())
		chanModesStr += 't';

	chanModesStr += args;
	return chanModesStr;
}

void	CmdExec::mode(t_cmdParser & cmd, Client *c)
{
	if (cmd.params.size() < 1)
		return (sendMsg(ERR_461, c, "MODE"));

	if (cmd.params[0][0] == '#')
	{
		Channel *chan = this->_srv->getChannelByName(cmd.params[0]);
		if (!chan)
			return (sendMsg(ERR_403, c, cmd.params[0]));
		
		if (cmd.params.size() == 1)
		{
			std::string chanModesStr = createChanModesStr(chan);
			std::string rpl324 = "324 " + c->getNickName() + " " + chan->getName() + " " + chanModesStr;
			return (sendMsg(rpl324, c, "", chan));
		}
		
		if (!chan->isOpe(c))
			return (sendMsg(ERR_482, c, "", chan));

	}
	else
	{
		Client *target = this->_srv->getClientByNick(cmd.params[0]);
		if (!target)
			return (sendMsg(ERR_401, c, cmd.params[0]));
		
		if (target != c)
			return (sendMsg(ERR_502, c));

		if (cmd.params.size() == 1)
		{
			std::string rpl221 = "221 " + c->getNickName() + " +";
			sendMsg(rpl221, c);			
		}
	}
	
}