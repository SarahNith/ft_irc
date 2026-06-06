/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:54:37 by skuor             #+#    #+#             */
/*   Updated: 2026/06/06 12:37:25 by skuor            ###   ########.fr       */
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
void	CmdExec::assignModes(t_cmdParser & cmd, Channel *chan, Client *c)
{
	std::string	modestring = cmd.params[1];
	std::vector<std::string>::iterator	it = cmd.params.begin() + 2;
	std::vector<std::string>::iterator	ite = cmd.params.end();
	
	char		sign = '+';
	
	for (size_t i = 0; i < modestring.size(); i++)
	{
		char	modeChar = modestring[i];
	
		if (modestring[i] == '+')
		{
			sign = '+';
			continue ;
		}	
		else if (modestring[i] == '-')
		{
			sign = '-';
			continue ;
		}

		switch(modeChar)
		{
			case 'i':
				chan->setInviteOnly(sign == '+');
				break ;
			case 't':
				chan->setTopicRestriction(sign == '+');
				break ;
			case 'k':
				if (it != ite)
				{
					if (sign == '+')
					{
						chan->setKey(*it);
						++it;
					}
					else
						chan->setKey("");
				}
				break ;
			case 'o':
				if (it != ite)
				{
					Client *target = this->_srv->getClientByNick(*it);
					if (!target)
						return (sendMsg(ERR_401, c, *it));
					else if (!chan->isMember(target))
						return (sendMsg(ERR_442, target, "", chan));
					if (sign == '+')
						chan->addOpe(target);
					else
						chan->removeOpe(target);
					++it;
				}
				break ;
			case 'l':				
				if (sign == '+')
				{
					if (it != ite)
					{
						size_t limit;
						std::stringstream ss(*it);
						ss >> limit;
						
						chan->setLimitCapacity(limit);
						++it;
					}
				}
				else
					chan->setLimitCapacity(0);
				break ;
			default:
				sendMsg(ERR_501, c, "", chan);
				break ;
		}
	}
	std::string prefix = prefixStr(c);
	
	std::vector<std::string>::iterator	itArgs = cmd.params.begin() + 1;
	std::string argsStr;
	for (itArgs; itArgs != cmd.params.end(); itArgs++)
		argsStr += *itArgs + " ";
	std::string msg = prefix + " MODE " + chan->getName() + " " +  argsStr;

	sendToAll(msg, *chan);
}

void	CmdExec::mode(t_cmdParser & cmd, Client *c)
{
	if (cmd.params.size() < 1)
		return (sendMsg(ERR_461, c, "MODE"));

	Channel *chan = this->_srv->getChannelByName(cmd.params[0]);

	if (cmd.params[0][0] == '#')
	{
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

		assignModes(cmd, chan, c);
		
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