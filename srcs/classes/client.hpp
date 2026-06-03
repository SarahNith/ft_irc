/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:03:54 by skuor             #+#    #+#             */
/*   Updated: 2026/06/03 17:13:58 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "../includes/base.hpp"

class Client {
	
	public:

		Client();
		Client(int fd);
		~Client();
	
		std::string	getNickName() const;
		std::string	getUserName() const;
		std::string	getRealName() const;
		std::string	getOldNickName() const;
		std::string getHostname() const;
		// std::string	getPrefix() const;
		
		bool	getCorrectPassword() const;
		bool	getAllInfo() const;
		bool	getSentWelcome() const;
		bool	getCompleteRegis() const;
		
		int		getClientFd() const;

		void	write(const std::string & msg);

		void	setNickName(const std::string & newName);
		void	setUserName(const std::string & newName);
		void	setRealName(const std::string & newName);

		void	setCorrectPassword(bool pw);
		void	setAllInfo(bool allInfo);
		void	setSentWelcome(bool isSent);
		void	setCompleteRegis(bool completed);

		
	private:
		int 		_clientFd;
		bool		_toDisconnect;
		
		std::string	_nickName; //affiche pour tlm
		std::string	_userName; //nom utilisateur systeme
		std::string	_realName; //donne lors de l'inscription
		std::string	_oldNickname;
		std::string	_hostname;
		
		bool		_correctPassword;
		bool		_allInfo;
		bool		_completeRegistration;
		bool		_sentWelcome;
		// int			_nbInfo;

		std::string	_readBuff; //stocke donnees recues du clients pas encore traitees
		std::string	_toSendBuff; //stocke donnees en attente d'etre envoyees au client;
		
		std::string	_userMode;

};

#endif