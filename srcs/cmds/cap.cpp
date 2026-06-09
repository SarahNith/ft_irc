/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 13:28:15 by skuor             #+#    #+#             */
/*   Updated: 2026/06/09 11:05:05 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec/cmdExec.hpp"

void	CmdExec::cap(t_cmdParser & cmd, Client *c)
{
	if (cmd.params.empty())
		return ;
	
	if (cmd.params[0] == "LS")
	{
		this->_srv->write("CAP response sent");
		return (sendMsg(RPL_CAP, c));
	}
	else if (cmd.params[0] == "END")
		return ;
}