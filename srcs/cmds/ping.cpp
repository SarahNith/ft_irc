/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 13:37:35 by skuor             #+#    #+#             */
/*   Updated: 2026/06/11 16:46:45 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec/cmdExec.hpp"

void	CmdExec::ping(t_cmdParser & cmd, Client *c)
{
	if (cmd.params.size() < 1 && cmd.trailing.empty())
		return (sendMsg(ERR_409, c));
	
	std::string msg;
	if (!cmd.params.empty())
		msg = "PONG ircserv :" + cmd.params[0];
	else if (!cmd.trailing.empty())
		msg = "PONG ircserv :" + cmd.trailing;
	write("PONG sent");
	sendMsg(msg, c);
}
