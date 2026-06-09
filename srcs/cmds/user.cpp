/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 19:20:00 by skuor             #+#    #+#             */
/*   Updated: 2026/06/09 16:22:50 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec/cmdExec.hpp"

void	CmdExec::user(t_cmdParser & cmd, Client *c)
{
	if (c == NULL)
		return ;
	
	if (c->getHasNick() && !c->getCorrectPassword())
		return ;
	if (cmd.params.size() < 3 || cmd.trailing.empty() || cmd.params[0].empty())
		return (sendMsg(ERR_461, c, "USER"));
	if (c->getCompleteRegis())
		return (sendMsg(ERR_462, c));

	c->setUserName(cmd.params[0]);
	c->setRealName(cmd.trailing);
	
	c->setHasUser(true);
	checkRegistration(c);
}