/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 17:50:13 by skuor             #+#    #+#             */
/*   Updated: 2026/05/28 19:08:47 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/base.hpp"

static bool	isWhitespace(char ws)
{
	if (ws == ' ' || ws == '\t')
		return true;
	return false;
}

t_commandParser	commandParser(std::string line)
{
	t_commandParser cp;
	
	int i = 0;
	size_t	ws1, ws2;
	if (line[0] == ':')
	{
		ws1 = line.find(' ');
		cp.prefix = line.substr(0, ws1);
	}
	
}