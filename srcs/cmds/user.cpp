/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 19:20:00 by skuor             #+#    #+#             */
/*   Updated: 2026/06/03 19:38:02 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec.hpp"

void	CmdExec::user(t_cmdParser & cmd, Client *c)
{
	if (cmd.params.size() < 3 || cmd.trailing.empty() || cmd.params[0].empty())
		return (sendMsg(ERR_461, c, "USER"));
	if (c->getCompleteRegis())
		return (sendMsg(ERR_462, c));

	c->setUserName(cmd.params[0]);
	c->setRealName(cmd.trailing);
	
	c->setHasUser(true);
	checkRegistration(c);
}