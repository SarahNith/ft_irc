/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:37:46 by skuor             #+#    #+#             */
/*   Updated: 2026/06/02 15:34:42 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/base.hpp"

Channel::Channel(Client* client, std::string name)
	: _name(name), _topic(""), _mode(""), _channelPassword(""), _capacityLimit(-1)
{
	addMember(client);
	addOpe(client);
}

Channel::~Channel() {}

/* ************ Getters ************ */

std::string	Channel::getName() const
{
	return _name;
}

std::string	Channel::getTopic() const
{
	return _topic;
}

std::string	Channel::getMode() const
{
	return _mode;
}

std::string	Channel::getChannelPassword() const
{
	return _channelPassword;
}

int			Channel::getCapacityLimit() const
{
	return _capacityLimit;
}

/* ************ Setters ************ */

void	Channel::setName(std::string newName)
{
	this->_name = newName;
}

void	Channel::setTopic(std::string newTopic)
{
	this->_topic = newTopic;
}

void	Channel::setMode(std::string newMode)
{
	this->_mode = newMode;
}

void	Channel::setPassword(std::string newPassword)
{
	this->_channelPassword = newPassword;
}

/* ************ Member functions ************ */

void	Channel::addMember(Client* member)
{
	_members.push_back(member);
}

void	Channel::removeMember(Client* member)
{
	std::vector<Client*>::iterator	it = std::find(_members.begin(), _members.end(), member);

	if (it != _members.end())
		_members.erase(it);

}

void	Channel::addOpe(Client* ope)
{
	_operators.push_back(ope);
}

void	Channel::removeOpe(Client* ope)
{
	std::vector<Client*>::iterator	it = std::find(_operators.begin(), _operators.end(), ope);
	
	if (it != _operators.end())
		_operators.erase(it);
}


bool	Channel::isMember(Client* client)
{
	std::vector<Client *>::iterator	it = _members.begin();
	std::vector<Client *>::iterator	ite = _members.end();

	while (ite != it)
	{
		if (*it == client)
			return true;
		++it;
	}
	return false;
}

bool	Channel::isOpe(Client* client)
{
	std::vector<Client *>::iterator	it = _operators.begin();
	std::vector<Client *>::iterator	ite = _operators.end();

	while (ite != it)
	{
		if (*it == client)
			return true;
		++it;
	}
	return false;
}
