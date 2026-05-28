/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:04:01 by skuor             #+#    #+#             */
/*   Updated: 2026/05/28 18:05:08 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/base.hpp"

Client::Client()
{
	_toDisconnect = false;
	_correctPassword = false;
	_allInfo = false;
	// _completeRegis = false;
	_sentWelcome = false;
	// _nbInfo = 0;
}

Client::~Client() {}

std::string	Client::getNickName() const
{
	return _nickName;	
}

std::string	Client::getUserName() const
{
	return _userName;
}

std::string	Client::getRealName() const
{
	return _realName;
}

std::string	Client::getOldNickName() const
{
	return _oldNickname; 
}

std::string Client::getHostname() const
{
	return _hostname;
}

int		Client::getClientFd() const
{
	return _clientFd;
}


void	Client::setNickName(const std::string & newName)
{
	this->_nickName = newName;
}

void	Client::setUserName(const std::string & newName)
{
	this->_userName = newName;
}

void	Client::setRealName(const std::string & newName)
{
	this->_realName = newName;		
}
