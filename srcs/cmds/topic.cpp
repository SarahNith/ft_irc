/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:08:09 by skuor             #+#    #+#             */
/*   Updated: 2026/06/06 12:35:45 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec/cmdExec.hpp"

void	CmdExec::topic(t_cmdParser & cmd, Client *c)
{
	if (cmd.params.size() < 1)
		return (sendMsg(ERR_461, c, "TOPIC"));

	Channel *chan = this->_srv->getChannelByName(cmd.params[0]);
	if (!chan)
		return (sendMsg(ERR_403, c, "", chan));

	if (!chan->isMember(c))
		return (sendMsg(ERR_442, c, "", chan));
	
	
	if (cmd.trailing.empty()) // checking topic
	{
		if (chan->getTopic().empty())
			sendMsg(RPL_331, c, "", chan);
		else
			sendMsg(RPL_332, c, "", chan);
	}
	else
	{
		if (chan->hasTopicRestriction())
		{
			if (!chan->isOpe(c))
				return (sendMsg(ERR_482, c, "", chan));
		}

		std::string prefix = prefixStr(c);
		
		if (cmd.trailing == " ")
		{
			chan->setTopic("");
			std::string clearTopicMsg = prefix + " TOPIC " + chan->getName() + " :";
			sendToAll(clearTopicMsg, *chan);
		}
		else
		{
			chan->setTopic(cmd.trailing);
			std::string newTopicMsg = prefix + " TOPIC " + chan->getName() + " :" + cmd.trailing;

			sendToAll(newTopicMsg, *chan);
		}
	}
	return ;
}