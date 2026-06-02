/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdExec.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:25:52 by skuor             #+#    #+#             */
/*   Updated: 2026/06/02 15:18:15 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/base.hpp"

CmdExec::CmdExec() {}
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
	}	
}

/* ************ COMMANDS ************ */

void	CmdExec::pass(t_cmdParser & cmd, Client *Client)
{
	if (cmd.params.size() < 1)
		return ; // err 461
	if ()
	
		
}
void	CmdExec::nick(t_cmdParser & cmd, Client *Client) {}
void	CmdExec::user(t_cmdParser & cmd, Client *Client) {}
void	CmdExec::join(t_cmdParser & cmd, Client *Client) {}
void	CmdExec::privmsg(t_cmdParser & cmd, Client *Client) {}
void	CmdExec::kick(t_cmdParser & cmd, Client *Client) {}
void	CmdExec::invite(t_cmdParser & cmd, Client *Client) {}
void	CmdExec::topic(t_cmdParser & cmd, Client *Client) {}
void	CmdExec::mode(t_cmdParser & cmd, Client *Client) {}

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
	else
		return UNKNOWN;
}

std::string	CmdExec::replaceAll(std::string str, std::string toReplace, std::string strReplace)
{
	std::string	newStr;
	size_t	i = 0;
	while (i < str.length())
	{
		if (toReplace == "")
			return str;
		if (str.compare(i, toReplace.length(), toReplace) == 0)
		{
			newStr += strReplace;
			i += toReplace.length();
		}
		else
		{
			newStr += str[i];
			i++;
		}
	}
	return (newStr);
}

void		CmdExec::errorMsg(int errCode, Client *client, )
{
	
}

