/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdExec.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:26:00 by skuor             #+#    #+#             */
/*   Updated: 2026/06/03 19:27:15 by skuor            ###   ########.fr       */
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

class CmdExec {
	
	public:
		CmdExec();	
		CmdExec(Server* srv);
		~CmdExec();

		void	execute(t_cmdParser & cmd, Client *Client);
			

	private:
	
		void	pass(t_cmdParser & cmd, Client *c);
		void	nick(t_cmdParser & cmd, Client *c);
		void	user(t_cmdParser & cmd, Client *c);
		void	join(t_cmdParser & cmd, Client *c);
		void	privmsg(t_cmdParser & cmd, Client *c);
		void	kick(t_cmdParser & cmd, Client *c);
		void	invite(t_cmdParser & cmd, Client *c);
		void	topic(t_cmdParser & cmd, Client *c);
		void	mode(t_cmdParser & cmd, Client *c);
		
		Type	detectTypeCmd(std::string cmd);

		Server*	_srv;

		bool		checkRegistration(Client *c);
		void		sendMsg(std::string msg, Client *c, std::string other = "");
		std::string	replaceAll(std::string msg, std::string toReplace, std::string strReplace);
};

#define RPL_PREFIX ":" SERVER_NAME " "

# define RPL_001 RPL_PREFIX "001 <nick> :Welcome to the IRC network <nick>!<user>@<host>"

//PASS
# define ERR_461 RPL_PREFIX "461 <client> <command> :Not enough parameters"
# define ERR_462 RPL_PREFIX "462 <client> :You may not reregister"
# define ERR_464 RPL_PREFIX "464 <client> :Password incorrect"

//NICK
# define ERR_431 RPL_PREFIX "431 <client> :No nickname given"
# define ERR_432 RPL_PREFIX "432 <client> <nick> :Erroneus nickname"
# define ERR_433 RPL_PREFIX "433 <client> <nick> :Nickname is already in use"



#endif