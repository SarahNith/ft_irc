/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:13:05 by skuor             #+#    #+#             */
/*   Updated: 2026/06/15 18:39:33 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <signal.h>
#include <vector>
#include <errno.h>

#include "colors.hpp"

typedef struct s_botParser
{
	std::string	nick;
	std::string	command;
	std::string	channel;
	std::string msg;
}			t_botParser;

class Bot {

	public:
		Bot(std::string ip, int port, std::string password);
		~Bot();
	
		void	recvLoop();
		void	connectToServer();
		void	run();
		void	handleLine(std::string line);
		void	registerBot();
		void	sendMsg(std::string msg);
		
		class Exception : public std::exception
		{
			public:

				Exception(std::string msg) : str(msg) {}
				~Exception() throw() {}

				const char* what() const throw()
				{
					return str.c_str();
				}

			private :
				std::string str;
				
		};
	
	private:

		static void	_signalhander(int num);
		
		std::string	_ip;
		int			_fd;
		int			_port;
		std::string _readBuf;
		static bool _signal;

		std::string					_password;
		std::vector<std::string>	_bannedWords;
		std::map<std::string, int>	_warnings;
		std::string					_channel;
		std::ifstream				_srcFile;
		
		void		_write(std::string msg);
		void		_loadBannedWords();
		t_botParser	_parsingLine(std::string line);
};

#endif