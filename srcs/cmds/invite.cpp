/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 14:13:15 by skuor             #+#    #+#             */
/*   Updated: 2026/06/11 15:44:23 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec/cmdExec.hpp"

void	CmdExec::invite(t_cmdParser & cmd, Client *c)
{
	if (cmd.params.size() < 2)
		return (sendMsg(ERR_461, c, "INVITE"));
	
	Channel *chan = this->_srv->getChannelByName(cmd.params[1]);
	if (chan == NULL)
		return (sendMsg(ERR_403, c, "", chan));

	if (!chan->isMember(c))
		return (sendMsg(ERR_442, c, "", chan));

	if (chan->isInviteOnly())
	{
		if (!chan->isOpe(c))
			return (sendMsg(ERR_482, c, "", chan));
	}

	Client *toInvite = this->_srv->getClientByNick(cmd.params[0]);
	if (!toInvite)
		return (sendMsg(ERR_401, c, cmd.params[0]));
	
	if (chan->isMember(toInvite))
		return (sendMsg(ERR_443, c, toInvite->getNickName(), chan));
	
	sendMsg(RPL_341, c, toInvite->getNickName(), chan);

	std::string prefix = prefixStr(c);
	std::string inviteMsg = prefix + " INVITE " + toInvite->getNickName() + " " + chan->getName();
	
	c->write("invited " + toInvite->getNickName() + " to the channel");
	sendMsg(inviteMsg, toInvite);
	chan->addToInviteList(toInvite);

	return ;
}