/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:04:01 by skuor             #+#    #+#             */
/*   Updated: 2026/05/27 16:39:56 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/base.hpp"

Client::Client()
{
	_toDisconnect = false;
	_correctPassword = false;
	_allInfo = false;
	// _completeRegis = false;
	_sentWelcome = false;
	// _nbInfo = 0;
}
