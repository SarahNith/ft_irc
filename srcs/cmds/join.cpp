/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:12:19 by skuor             #+#    #+#             */
/*   Updated: 2026/06/09 10:49:03 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec/cmdExec.hpp"

std::map<std::string, std::string>	parsingJoin(t_cmdParser & cmd)
{
	std::map<std::string, std::string> channels;
	if (cmd.params.empty())
		return channels;
		
	std::string chanStr = cmd.params[0];
	std::string keyStr = "";
	if (cmd.params.size() >= 2)
		keyStr = cmd.params[1];
		
	std::vector<std::string> chans;
	std::vector<std::string> keys;
	
	size_t commaPos = chanStr.find(',');
	while (commaPos != std::string::npos)
	{
		chans.push_back(chanStr.substr(0, commaPos));
		chanStr = chanStr.substr(commaPos + 1);
		commaPos = chanStr.find(',');
	}
	chans.push_back(chanStr);
	
	if (!keyStr.empty())
	{
		commaPos = keyStr.find(',');
		while (commaPos != std::string::npos)
		{
			keys.push_back(keyStr.substr(0, commaPos));
			keyStr = keyStr.substr(commaPos + 1);
			commaPos = keyStr.find(',');
		}
		keys.push_back(keyStr);	
	}

	for (size_t i = 0; i < chans.size(); i++)
	{
		if (i < keys.size())
			channels[chans[i]] = keys[i];
		else
			channels[chans[i]] = "";
	}
	
	return channels;
}

void	CmdExec::sendNames(Client *c, Channel & ch)
{
	std::vector<Client*> members = ch.getMembers();
	
	std::vector<Client*>::iterator it;
	std::vector<Client*>::iterator ite = members.end();

	std::string nickList;
	
	for (it = members.begin(); it != ite; it++)
	{
		if (ch.isOpe(*it))
			nickList += "@" + (*it)->getNickName() + " ";
		else
			nickList += (*it)->getNickName() + " ";
	}

	std::string msg = ":ircserv 353 " + c->getNickName() + " = " + ch.getName() + " :" + nickList;
	sendMsg(msg, c, "", &ch);
	sendMsg(RPL_366, c, "", &ch);
	ch.write("Client list sent");
}

void	CmdExec::join(t_cmdParser & cmd, Client *c)
{
	if (cmd.params.size() < 1)
		return (sendMsg(ERR_461, c, "JOIN"));
		
	std::map<std::string, std::string> channels = parsingJoin(cmd); // chan, key
	std::map<std::string, std::string>::iterator it = channels.begin();
	
	std::map<std::string, Channel> &chansList = this->_srv->getChannels(); //liste des chans sur le serveur
	std::map<std::string, Channel>::iterator it1;

	std::string prefix = prefixStr(c);
	
	if (cmd.params[0] == "0")
	{
		for (it1 = chansList.begin(); it1 != chansList.end(); it1++)
		{
			if (it1->second.isMember(c))
			{
				it1->second.write("Member removed : " + c->getNickName());
				std::string partMsg = prefix + " PART " + it1->first;
				sendToAll(partMsg, it1->second);
				it1->second.removeMember(c);
				it1->second.removeOpe(c);
			}
		}
		return ;
	}

	while (it != channels.end())
	{
		if (it->first[0] != '#' || it->first.size() > CHANLEN)
		{
			sendMsg(ERR_476, c, it->first);
			it++;
			continue ;
		}
		
		std::string msg = prefix + " JOIN " + it->first;
		std::map<std::string, Channel>::iterator itSrv = chansList.find(it->first);
		if (itSrv == chansList.end()) //chan n'existe pas encore
		{
			//je cree un nouveau chan et ajoute le user en tant que member et ope
			// chansList[it->first] = Channel(c, it->first);
			chansList.insert(std::make_pair(it->first, Channel(c, it->first)));
			sendToAll(msg, chansList[it->first]);
			sendNames(c, chansList[it->first]);
			chansList[it->first].write("New chan created");
			it++;
			continue ;
		}
		else
		{
			if (itSrv->second.isMember(c))
			{
				it++;
				continue ;
			}
			else
			{
				//chan sur invitation
				if (itSrv->second.isInviteOnly())
				{
					if (!itSrv->second.isInvited(c))
					{
						sendMsg(ERR_473, c, itSrv->first);
						it++;
						continue ;
					}
				}
				//chan avec mdp
				if (!itSrv->second.getChannelKey().empty())
				{
					if (it->second != itSrv->second.getChannelKey())
					{
						sendMsg(ERR_475, c, itSrv->first);
						it++;
						continue ;
					}
				}
				//chan avec limitation nb mb
				if (itSrv->second.getLimitCapacity())
				{
					if (itSrv->second.getMembers().size() >= itSrv->second.getLimitCapacity())
					{
						sendMsg(ERR_471, c, itSrv->first);
						it++;
						continue ;
					}
				}
				itSrv->second.addMember(c);
				sendToAll(msg, itSrv->second);

				if (!itSrv->second.getTopic().empty())
					sendMsg(RPL_332, c, "", &itSrv->second);

				sendNames(c, itSrv->second);
			}
		}
		it++;			
	}
}
