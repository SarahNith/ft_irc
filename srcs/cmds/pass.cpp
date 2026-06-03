/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:59:52 by skuor             #+#    #+#             */
/*   Updated: 2026/06/03 11:00:34 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdExec.hpp"

void	CmdExec::pass(t_cmdParser & cmd, Client *Client)
{
	std::string	correctPw = this->_srv->getPassword();
	
	if (cmd.params.size() < 1)
		return (errorMsg(ERR_461, Client, "PASS")); 
	if (Client->getCorrectPassword() || Client->getCompleteRegis())
		return (errorMsg(ERR_462, Client));

	std::string	password = cmd.params[0];

	if (password != correctPw)
		return (errorMsg(ERR_464, Client));
	else
		Client->setCorrectPassword(true);		
}
