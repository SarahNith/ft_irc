/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 17:50:13 by skuor             #+#    #+#             */
/*   Updated: 2026/05/29 12:10:06 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/base.hpp"

static bool	isWhitespace(char ws)
{
	if (ws == ' ' || ws == '\t')
		return true;
	return false;
}
static size_t	skip_ws(std::string line, size_t i)
{
	while (i < line.length() && isWhitespace(line[i]))
		i++;
	return (i);
}

t_commandParser	commandParser(std::string line)
{
	t_commandParser cp;
	size_t	pos = 0;
	
	if (line[0] == ':')
	{
		pos = line.find_first_of(" \t", 0);
		if (pos != std::string::npos)
		{
			cp.prefix = line.substr(1, pos - 1);
			pos = pos + 1;
		}
		else
			pos = line.length();
	}
	pos = skip_ws(line, pos);
	size_t wsPos = line.find_first_of(" \t", pos);
	if (wsPos != std::string::npos)
	{
		cp.command = line.substr(pos, wsPos - pos);
		pos = pos + 1;
	}
	else
	{
		cp.command = line.substr(pos);	
		pos = line.length();
	}
	return cp;
}

void test_parser()
{
    // Cas 1 : avec prefix
    t_commandParser cp1 = commandParser(":nick!user@host PRIVMSG #channel hello");
    std::cout << "Prefix: [" << cp1.prefix << "], Command: [" << cp1.command << "]" << std::endl;
    
    // Cas 2 : sans prefix
    t_commandParser cp2 = commandParser("PRIVMSG #channel hello");
    std::cout << "Prefix: [" << cp2.prefix << "], Command: [" << cp2.command << "]" << std::endl;
    
    // Cas 3 : command seule
    t_commandParser cp3 = commandParser("PING");
    std::cout << "Prefix: [" << cp3.prefix << "], Command: [" << cp3.command << "]" << std::endl;
}