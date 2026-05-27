/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:03:54 by skuor             #+#    #+#             */
/*   Updated: 2026/05/27 12:51:29 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "../includes/base.hpp"

class Client {
	
	public:
		Client();
		~Client();

	private:
		int 		_clientFd;
		bool		_toDisconnect;
		
		std::string	_nickName; //affiche pour tlm
		std::string	_userName; //nom utilisateur systeme
		std::string	_realName; //donne lors de l'inscription
		std::string	_oldNickname;
		
		bool		_correctPassword;
		bool		_allInfo;
		bool		_completeRegis;
		bool		_sentWelcome;
		int			_nbInfo;

		std::string	_readBuff; //stocke donnees recues du clients pas encore traitees
		std::string	_toSendBuff; //stocke donnees en attente d'etre envoyees au client;
		
		std::string	_userMode;

};

#endif