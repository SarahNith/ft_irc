/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:59:52 by skuor             #+#    #+#             */
/*   Updated: 2026/06/03 18:55:09 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec.hpp"

void	CmdExec::pass(t_cmdParser & cmd, Client *c)
{
	std::string	correctPw = this->_srv->getPassword();
	
	if (cmd.params.size() < 1)
		return (sendMsg(ERR_461, c, "PASS")); 
	if (c->getCorrectPassword() || c->getCompleteRegis())
		return (sendMsg(ERR_462, c));

	std::string	password = cmd.params[0];

	if (password != correctPw)
		return (sendMsg(ERR_464, c));
	else
		c->setCorrectPassword(true);
}
