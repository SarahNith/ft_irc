/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:13:05 by skuor             #+#    #+#             */
/*   Updated: 2026/06/12 16:35:17 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

#include <string>
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

#include "colors.hpp"

class Bot {

	public:
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
		
		void	_write(std::string msg);
};

#endif