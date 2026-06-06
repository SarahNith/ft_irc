/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 10:39:14 by skuor             #+#    #+#             */
/*   Updated: 2026/06/06 12:24:59 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec/cmdExec.hpp"

static std::vector<std::string>	parsingUsers(t_cmdParser & cmd)
{
	std::vector<std::string>	users;
	if (cmd.params.empty())
		return users;

	std::string	param = cmd.params[1];

	size_t commaPos = param.find(',');
	while (commaPos != std::string::npos)
	{
		users.push_back(param.substr(0, commaPos));
		param = param.substr(commaPos + 1);
		commaPos = param.find(',');
	}
	users.push_back(param);
	return users;
}

void	CmdExec::kick(t_cmdParser & cmd, Client *c)
{
	if (cmd.params.size() < 2)
		return (sendMsg(ERR_461, c, "KICK"));

	Channel *chan = this->_srv->getChannelByName(cmd.params[0]);
	if (chan == NULL)
		return (sendMsg(ERR_403, c, "", chan));

	if (!chan->isMember(c))
		return (sendMsg(ERR_442, c, "", chan));

	if (!chan->isOpe(c))
		return (sendMsg(ERR_482, c, "", chan));

	std::vector<std::string> users = parsingUsers(cmd);
	std::vector<std::string>::iterator	it;

	for (it = users.begin(); it != users.end(); it++)
	{
		std::string reason = cmd.trailing.empty() ? "You have been kicked" : cmd.trailing;
		std::string prefix = prefixStr(c);
		
		std::string msg = prefix + " KICK " + cmd.params[0] + " " + *it + " :" + reason;
			
		Client *dest = this->_srv->getClientByNick(*it);
		if (!dest || !chan->isMember(dest))
			sendMsg(ERR_441, c, *it, chan);
		else
		{
			sendToAll(msg, *chan);
			chan->removeMember(dest);
			if (chan->isOpe(dest))
				chan->removeOpe(dest);
		}
	}
	return ;
}