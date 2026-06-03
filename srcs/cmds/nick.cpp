/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:59:08 by skuor             #+#    #+#             */
/*   Updated: 2026/06/03 12:41:40 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec.hpp"

static bool	validNickname(std::string nickname)
{
	if (nickname.empty())
		return false;
	if (nickname.size() > 9)
		return false;
	for (size_t i = 0; i < nickname.length(); i++)
	{
		if (!(isalpha(nickname[i]) || isdigit(nickname[i]) || strchr("[]{}\\|", nickname[i])))
			return false;
	}
	if (isdigit(nickname[0]) || nickname[0] == '#' || nickname[0] == ':')
		return false;
	return true;
}

void	CmdExec::nick(t_cmdParser & cmd, Client *c)
{
	if (!c->getCorrectPassword())
		return ;
	if (cmd.params.size() < 1)
		return (errorMsg(ERR_431, c));
	
	std::string nickname = cmd.params[0];

	if (!validNickname(nickname))
		return (errorMsg(ERR_432, c, nickname));
	
	Client *foundNick = _srv->getClientByNick(nickname);
	if (foundNick != NULL)
		return (errorMsg(ERR_433, c, nickname));	
}

