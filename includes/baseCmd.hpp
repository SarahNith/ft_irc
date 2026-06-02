/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   baseCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:16:48 by mkhoury           #+#    #+#             */
/*   Updated: 2026/05/27 16:25:25 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASECMD_HPP
#define BASECMD_HPP

#include "base.hpp"
#define WHI "\e[0;37m" 

// Cap ls
#define CAP_LS ":<server name> CAP END"

// Pass
#define ERR_461 ":<server name> 461 <client nick> :Not enough params"
#define ERR_462 ":<server name> 462 <client nick> :User already registered"
#define ERR_464 ":<server name> 464 <client nick> :Pass Password incorrect"

// Nick
#define ERR_431 ":<server name> 431 <client nick> :No nickname given"
#define ERR_432 ":<server name> 432 <client nick> :Invalid nickname"
#define ERR_433 ":<server name> 433 <client nick> <nick> :Nickname already in use"

// CHANNEL ERRORS
#define ERR_401 ":<server name> 401 <nick> <target> :No such nick/channel"
#define ERR_403 ":<server name> 403 <nick> <channel> :No such channel"
#define ERR_441 ":<server name> 441 <nick> <target> <channel> :They aren't on that channel"
#define ERR_442 ":<server name> 442 <nick> <channel> :You're not on that channel"
#define ERR_443 ":<server name> 443 <nick> <channel> :You are already on channel"
#define CHANERR_461 ":<server name> 461 <nick> <command> :Not enough params"
#define ERR_471 ":<server name> 471 <nick> <channel> :Cannot join channel (+l)"
#define ERR_472 ":<server name> 472 <nick> <mode> :Unknown mode"
#define ERR_473 ":<server name> 473 <nick> <channel> :Cannot join channel (+i)"
#define ERR_475 ":<server name> 475 <nick> <channel> :Cannot join channel (+k)"
#define ERR_482 ":<server name> 482 <nick> <channel> :You're not channel operator"
#define ERR_696 ":<server name> 696 <nick> <mode> :Invalid mode specified"
#define ERR_TOPICLEN "437 Topic name is too long"
   

// RPL
#define RPL_001 ":<server name> 001 <client nick> :Welcome to the 42 irc Network, <client nick>"
#define RPL_002 ":<server name> 002 <client nick> :Your host is <server name>, running version V1.0"
#define RPL_003 ":<server name> 003 <client nick> :This server was created <datetime>"
#define RPL_004 ":<server name> 004 <client nick> <server name> V1.0 ors itkol"
#define RPL_005 ":<server name> 005 <client nick> NICKLEN=<nicklen> CHANNELLEN=<chanlen> TOPICLEN=<topiclen> :are supported by this server"
#define RPL_315 ":<server name> 315 <client> <mask> :End of WHO list"
#define RPL_352 ":<server name> 352 <client> <channel> <username> <host> <server> <nick> <flags> :<hopcount> <realname>";
#define ERROR ":<server name> ERROR <client nick> :<error msg>"

#define REGIST  ":<server name> 451 <client nick>: You have not registered"

// #define RPL_251 ":<server name> 251 <client nick> :There are <nb users> users and 0 invisible on 1 servers"
// #define RPL_252 ":<server name> 252 <client nick> 0 :operator(s) online"
// #define RPL_253 ":<server name> 253 <client nick> <pending connections> :unknown connection(s)"
// #define RPL_254 ":<server name> 254 <client nick> <channels> :channels formed"
// #define RPL_255 ":<server name> 255 <client nick> :I have <nb clients> clients and 1 servers"
// #define RPL_265 ":<server name> 265 <client nick> [<u> <m>] :Current local users <u>, max <m>"
// #define RPL_266 ":<server name> 266 <client nick> [<u> <m>] :Current global users <u>, max <m>"

// MOTD
#define RPL_372 ":<server name> 372 <client nick> :THIS IS MESSAGE OF THE DAY"
#define RPL_376 ":<server name> 376 <client nick> :End of /MOTD command."

// MSG
#define PRIVMSG ":<sender> PRIVMSG <target> <msg>"
#define CHANMSG ":<client nick>!~<username>@localhost PRIVMSG <target> <msg>"


// KICK
#define KICKMSG ":<client nick>!~<username>@localhost KICK <channel> <target> :<message>"

// INVITE
#define INVITEMSG ":<client nick>!~<username>@localhost INVITE <target> <channel>" 
#define RPL_341   ":<server name> 341 <client nick> <target> <channel>"

// TOPIC
#define TOPICMSG ":<client nick>!~<username>@localhost TOPIC <target> :<topic>"

// MODE
#define MODEMSG ":<servername> <sender> MODE <target> <mode>"
// bon format ?

#define JOINMSG    ":<client nick>!~<username>@localhost JOIN :<channel>"

// PART
#define MPART    ":<client nick>!~<username>@localhost PART <channel>"

//CHANNEL ERRORS
#define ERR_471 ":<server name> 471 <nick> <channel> :Cannot join channel (+l)"
#define ERR_473 ":<server name> 473 <nick> <channel> :Cannot join channel (+i)"
#define ERR_475 ":<server name> 475 <nick> <channel> :Cannot join channel (+k)"

// INPUT TOO LONG
#define ERR_417 ":<server name> 417 <client nick> :Input line was too long"

class Server;
class Client;

class BaseCmd
{
	public:
	BaseCmd(std::string line);

	std::string getCmdName(void);
	std::string getRaw(void);
	std::vector<std::string> getVector(void);
	void	write(std::string msg){std::cout << CYAN << "Command " + cmd_name + " : "+ WHI + msg << std::endl;};


	protected:
		
		std::string Raw;
		std::string cmd_name;
		std::vector<std::string> cmdVector;
};

class Commands
{
	public:
	
		static void CMD_CAP(Server &server, Client &client, BaseCmd cmd);
		static void CMD_USER(Server &server, Client &client, BaseCmd cmd);
		static void CMD_PASS(Server &server, Client &client, BaseCmd cmd);
		static void CMD_NICK(Server &server, Client &client, BaseCmd cmd);
		static void CMD_PING(Server &server, Client &client, BaseCmd cmd);
		static void CMD_JOIN(Server &server, Client &client, BaseCmd cmd);
		static void CMD_PRIVMSG(Server &server, Client &client, BaseCmd cmd);
		static void CMD_CHANMSG(Server &server, Client &client, BaseCmd cmd);
		static void CMD_TOPIC(Server &server, Client &client, BaseCmd cmd);
		static void CMD_KICK(Server &server, Client &client, BaseCmd cmd);
		static void CMD_INVITE(Server &server, Client &client, BaseCmd cmd);
		static void CMD_MODE(Server &server, Client &client, BaseCmd cmd);
		static void CMD_PART(Server &server, Client &client, BaseCmd cmd);

		static void CMD_PONG(Server &server, Client &client, BaseCmd cmd);
		static void SEND_RPL(Server &Server, Client &Client);
		static void CMD_QUIT(Server &Server, Client &Client, BaseCmd cmd);
};

#endif