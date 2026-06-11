/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:59:08 by skuor             #+#    #+#             */
/*   Updated: 2026/06/11 12:42:41 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec/cmdExec.hpp"

static bool	validNickname(std::string nickname)
{
	if (nickname.empty())
		return false;
	if (nickname.size() > NICKLEN)
		return false;
	for (size_t i = 0; i < nickname.length(); i++)
	{
		if (!(isalpha(nickname[i]) || isdigit(nickname[i]) || std::strchr("[]{}\\|_", nickname[i])))
			return false;
	}
	if (isdigit(nickname[0]) || nickname[0] == '#' || nickname[0] == ':')
		return false;
	return true;
}

void	CmdExec::nick(t_cmdParser & cmd, Client *c)
{
	if (c == NULL)
		return ;
	
	if (c->getHasUser() && !c->getCorrectPassword())
		return (write("You must enter PASS first"));
		
	if (cmd.params.size() < 1)
		return (sendMsg(ERR_431, c));
	
	std::string nickname = cmd.params[0];

	if (!validNickname(nickname))
		return (sendMsg(ERR_432, c, nickname));
	
	Client *foundNick = _srv->getClientByNick(nickname);
	if (foundNick != NULL)
		return (sendMsg(ERR_433, c, nickname));

	if (c->getNickName() != "*")
	{
		c->setOldNickName(c->getNickName());
		c->setNickName(nickname);
		std::string msg = ":" + c->getOldNickName() + "!" + c->getUserName() + "@"
			+ c->getHostname() + " NICK " + nickname;
		sendMsg(msg, c);
		c->write("User changed nickname to: " + nickname);
	}
	else
	{
		c->setNickName(nickname);
		c->write("User nickname: " + nickname);
	}

	c->setHasNick(true);
	checkRegistration(c);
}

