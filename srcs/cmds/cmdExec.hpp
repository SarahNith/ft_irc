/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdExec.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:26:00 by skuor             #+#    #+#             */
/*   Updated: 2026/06/02 17:26:53 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDEXEC_HPP
# define COMMANDEXEC_HPP

#include "../../includes/base.hpp"

enum Type
{
	PASS,
	NICK,
	USER,
	JOIN,
	PRIVMSG,
	KICK,
	INVITE,
	TOPIC,
	MODE,
	UNKNOWN
};

# define ERR_461 "461 <nickname> <command> :Not enough parameters"
# define ERR_462 "462 <nickname> :You may not reregister"
# define ERR_464 "464 <nickname> :Password incorrect"

class CmdExec {
	
	public:
		CmdExec();	
		CmdExec(Server* srv);
		~CmdExec();

		void	execute(t_cmdParser & cmd, Client *Client);
		void		errorMsg(std::string errMsg, Client *client, std::string cmd = "");
		

	private:
	
		void	pass(t_cmdParser & cmd, Client *Client);
		// void	nick(t_cmdParser & cmd, Client *Client);
		// void	user(t_cmdParser & cmd, Client *Client);
		// void	join(t_cmdParser & cmd, Client *Client);
		// void	privmsg(t_cmdParser & cmd, Client *Client);
		// void	kick(t_cmdParser & cmd, Client *Client);
		// void	invite(t_cmdParser & cmd, Client *Client);
		// void	topic(t_cmdParser & cmd, Client *Client);
		// void	mode(t_cmdParser & cmd, Client *Client);
		
		Type	detectTypeCmd(std::string cmd);

		Server*	_srv;

		// void		errorMsg(std::string errMsg, Client *client, std::string cmd = "");
		std::string	replaceAll(std::string msg, std::string toReplace, std::string strReplace);
};

#endif