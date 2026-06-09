/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:37:46 by skuor             #+#    #+#             */
/*   Updated: 2026/06/09 10:56:58 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/base.hpp"

Channel::Channel() {}

Channel::Channel(Client* client, std::string name)
	: _name(name), _topic("")
{
	_chanModes.inviteOnly = false;
	_chanModes.topicRestriction = false;
	_chanModes.key = "";
	_chanModes.limit = 0;
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

std::string	Channel::getChannelKey() const
{
	return _chanModes.key;
}

size_t		Channel::getLimitCapacity() const
{
	return _chanModes.limit;
}

bool	Channel::isInviteOnly() const
{
	return _chanModes.inviteOnly;
}

bool	Channel::hasTopicRestriction() const
{
	return _chanModes.topicRestriction;
}

std::vector<Client*>	Channel::getOpe() const
{
	return _operators;
}

std::vector<Client*>	Channel::getMembers() const
{
	return _members;
}

std::vector<Client*>	Channel::getInviteList() const
{
	return _inviteList;
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

void	Channel::setKey(std::string newKey)
{
	this->_chanModes.key = newKey;
}

void	Channel::setLimitCapacity(size_t newLimit)
{
	if (newLimit > 1000)
		return (write("Invalid limit capacity"));
	this->_chanModes.limit = newLimit;
}

void	Channel::setInviteOnly(bool isInviteOnly)
{
	this->_chanModes.inviteOnly = isInviteOnly;
}

void	Channel::setTopicRestriction(bool hasTopRestriction)
{
	this->_chanModes.topicRestriction = hasTopRestriction;
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

void	Channel::addToInviteList(Client* invited)
{
	_inviteList.push_back(invited);
}

void	Channel::removeFromInviteList(Client* member)
{
	std::vector<Client*>::iterator	it = std::find(_inviteList.begin(), _inviteList.end(), member);
	
	if (it != _inviteList.end())
		_inviteList.erase(it);
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

bool	Channel::isInvited(Client* client)
{
	std::vector<Client *>::iterator	it = _inviteList.begin();
	std::vector<Client *>::iterator	ite = _inviteList.end();

	while (ite != it)
	{
		if (*it == client)
			return true;
		++it;
	}
	return false;
}

void	Channel::write(std::string msg)
{
	std::cout << YELLOW << _name << " : " << DEFAULT << msg << std::endl;
}
