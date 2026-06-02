/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdExec.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:26:00 by skuor             #+#    #+#             */
/*   Updated: 2026/06/02 15:11:38 by skuor            ###   ########.fr       */
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

# define ERR_461 "<client> <command> :Not enough parameters"
# define ERR_462 "<client> :You may not reregister"
# define ERR_464 "<client> :Password incorrect"

class CmdExec {
	
	public:
		CmdExec();
		~CmdExec();

		void	execute(t_cmdParser & cmd, Client *Client);

	private:
	
		void	pass(t_cmdParser & cmd, Client *Client);
		void	nick(t_cmdParser & cmd, Client *Client);
		void	user(t_cmdParser & cmd, Client *Client);
		void	join(t_cmdParser & cmd, Client *Client);
		void	privmsg(t_cmdParser & cmd, Client *Client);
		void	kick(t_cmdParser & cmd, Client *Client);
		void	invite(t_cmdParser & cmd, Client *Client);
		void	topic(t_cmdParser & cmd, Client *Client);
		void	mode(t_cmdParser & cmd, Client *Client);
		
		Type	detectTypeCmd(std::string cmd);

		void		errorMsg(std::string errCode, Client *client);
		std::string	replaceAll(std::string msg, std::string toReplace, std::string strReplace);
};

#endif