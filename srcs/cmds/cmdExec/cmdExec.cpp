/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdExec.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:25:52 by skuor             #+#    #+#             */
/*   Updated: 2026/06/06 15:01:03 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec.hpp"

CmdExec::CmdExec() {}
CmdExec::CmdExec(Server* srv) : _srv(srv) {}
CmdExec::~CmdExec() {}

/* ************ Member functions ************ */

/* ************ EXEC ************ */

void	CmdExec::execute(t_cmdParser & cmd, Client *Client)
{
	std::string command = cmd.command;
	Type	cmdType = detectTypeCmd(command);

	switch(cmdType)
	{
		case UNKNOWN:
			return ;
		case PASS:
			this->pass(cmd, Client);
			break ;
		case NICK:
			this->nick(cmd, Client);
			break ;
		case USER:
			this->user(cmd, Client);
			break ;
		case JOIN:
			this->join(cmd, Client);
			break ;
		case PRIVMSG:
			this->privmsg(cmd, Client);
			break ;
		case KICK:
			this->kick(cmd, Client);
			break ;
		case INVITE:
			this->invite(cmd, Client);
			break ;
		case TOPIC:
			this->topic(cmd, Client);
			break ;
		case MODE:
			this->mode(cmd, Client);
			break ;
		case CAP:
			this->cap(cmd, Client);
			break ;
		case PING:
			this->ping(cmd, Client);
		case QUIT:
			this->ping(cmd, Client);
			break ;
	}	
}

/* ************ Helpers ************ */

Type	CmdExec::detectTypeCmd(std::string cmd)
{
	if (cmd == "PASS")
		return PASS;
	else if (cmd == "NICK")
		return NICK;
	else if (cmd == "USER")
		return USER;
	else if (cmd == "JOIN")
		return JOIN;
	else if (cmd == "PRIVMSG")
		return PRIVMSG;
	else if (cmd == "KICK")
		return KICK;
	else if (cmd == "INVITE")
		return INVITE;
	else if (cmd == "TOPIC")
		return TOPIC;
	else if (cmd == "MODE")
		return MODE;
	else if (cmd == "CAP")
		return CAP;
	else if (cmd == "PING")
		return PING;
	else if (cmd == "QUIT")
		return QUIT;
	else
		return UNKNOWN;
}

bool	CmdExec::checkRegistration(Client *c)
{
	if (!c->getCorrectPassword())
		return false;
	else if (!c->getHasNick())
		return false;
	else if (!c->getHasUser())
		return false;
	else
	{
		if (c->getCompleteRegis())
			return true;
		sendMsg(RPL_001, c);
		c->setCompleteRegis(true);
	}
	return true;
}
