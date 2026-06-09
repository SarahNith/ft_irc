/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdExec.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:26:00 by skuor             #+#    #+#             */
/*   Updated: 2026/06/09 09:52:16 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDEXEC_HPP
# define COMMANDEXEC_HPP

#include "../../../includes/base.hpp"

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
	CAP,
	PING,
	QUIT,
	PART,
	UNKNOWN
};

class CmdExec {
	
	public:
		CmdExec();	
		CmdExec(Server* srv);
		~CmdExec();

		void	execute(t_cmdParser & cmd, Client *Client);
		void	write(std::string msg);

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
		void	cap(t_cmdParser & cmd, Client *c);
		void	ping(t_cmdParser & cmd, Client *c);
		void	quit(t_cmdParser & cmd, Client *c);
		void	part(t_cmdParser & cmd, Client *c);
		
		Type	detectTypeCmd(std::string cmd);

		Server*	_srv;

		bool		checkRegistration(Client *c);
		
		void		sendMsg(std::string msg, Client *c, std::string other = "", Channel *ch = NULL);
		void		sendToAll(std::string msg, Channel &ch);
		void		sendToAllExcept(std::string msg, Channel &ch, Client *Except);
		std::string	prefixStr(Client *c);

		void		sendNames(Client *c, Channel & ch);
		void		assignModes(t_cmdParser & cmd, Channel *chan, Client *c);
		std::string	replaceAll(std::string msg, std::string toReplace, std::string strReplace);
};

# define NICKLEN 9
# define CHANLEN 10
# define TOPICLEN 20

#define RPL_PREFIX ":" SERVER_NAME " "

# define ERR_421 RPL_PREFIX "421 <client> <command> :Unknown command"

# define RPL_001 RPL_PREFIX "001 <nick> :Welcome to the IRC network <nick>!<user>@<host>"
# define RPL_002 RPL_PREFIX "002 <client> :Your host is ircserv, running version 1.0"
# define RPL_003 RPL_PREFIX "003 <client> :This server was created <datetime>"
# define RPL_004 RPL_PREFIX "004 <client> ircserv 1.0 o itkol"
# define RPL_005 RPL_PREFIX "005 <client> NICKLEN=9 CHANLEN=10 TOPICLEN=20 :are supported by this server"
# define RPL_372 RPL_PREFIX "372 <client> :Welcome to ft_irc!"
# define RPL_376 RPL_PREFIX "376 <client> :End of /MOTD command."

//PASS
# define ERR_461 RPL_PREFIX "461 <client> <command> :Not enough parameters"
# define ERR_462 RPL_PREFIX "462 <client> :You may not reregister"
# define ERR_464 RPL_PREFIX "464 <client> :Password incorrect"

//NICK
# define ERR_431 RPL_PREFIX "431 <client> :No nickname given"
# define ERR_432 RPL_PREFIX "432 <client> <nick> :Erroneus nickname"
# define ERR_433 RPL_PREFIX "433 <client> <nick> :Nickname is already in use"

//JOIN
# define RPL_332 RPL_PREFIX "332 <client> <channel> :<topic>"
# define RPL_366 RPL_PREFIX "366 <client> <channel> :End of /NAMES list"
# define ERR_471 RPL_PREFIX "471 <client> <channel> :Cannot join channel (+l)"
# define ERR_473 RPL_PREFIX "473 <client> <channel> :Cannot join channel (+i)"
# define ERR_475 RPL_PREFIX "475 <client> <channel> :Cannot join channel (+k)"
# define ERR_476 RPL_PREFIX "476 <client> <channel> :Bad Channel Mask"

//PRIVMSG
# define ERR_401 RPL_PREFIX "401 <client> <nick> :No such nick"
# define ERR_403 RPL_PREFIX "403 <client> <channel> :No such channel"
# define ERR_404 RPL_PREFIX "404 <client> <channel> :Cannot send to channel"
# define ERR_411 RPL_PREFIX "411 <client> :No recipient given (<command>)"
# define ERR_412 RPL_PREFIX "412 <client> :No text to send"

//KICK
# define ERR_441 RPL_PREFIX "441 <client> <nick> <channel> :They aren't on that channel"
# define ERR_442 RPL_PREFIX "442 <client> <channel> :You're not on that channel"
# define ERR_482 RPL_PREFIX "482 <client> <channel> :You're not channel operator"

//INVITE
# define RPL_341 RPL_PREFIX "341 <client> <nick> <channel>"
# define ERR_443 RPL_PREFIX "443 <client> <nick> <channel> :is already on channel"

//TOPIC
# define RPL_331 RPL_PREFIX "331 <client> <channel> :No topic is set"

//MODE
// # define RPL_221 RPL_PREFIX "221 <client> <modes>"
// # define RPL_324 RPL_PREFIX "324 <client> <channel> <modestring> <mode arguments>..."
# define ERR_501 RPL_PREFIX "501 <client> :Unknown MODE flag"
# define ERR_502 RPL_PREFIX "502 <client> :Cant change mode for other users"

//CAP
# define RPL_CAP RPL_PREFIX "CAP * LS :"

//PING
# define ERR_409 RPL_PREFIX "409 <client> :No origin specified"

#endif