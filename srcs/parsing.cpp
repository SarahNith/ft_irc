/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 17:50:13 by skuor             #+#    #+#             */
/*   Updated: 2026/06/02 12:20:49 by skuor            ###   ########.fr       */
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

t_cmdParser	cmdParser(std::string line)
{
	t_cmdParser cp;
	size_t	pos = 0;
	
	if (line.empty())
		return cp;
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
		pos = wsPos + 1;
	}
	else
	{
		cp.command = line.substr(pos);	
		pos = line.length();
	}

	pos = skip_ws(line, pos);
	
	wsPos = line.find_first_of(" \t", pos);
	while (wsPos != std::string::npos)
	{
		std::string param = line.substr(pos, wsPos - pos);

		if (param[0] == ':')
		{
			cp.trailing = param.substr(1);
			break ;
		}
		cp.params.push_back(param);
		pos = wsPos + 1;
		pos = skip_ws(line, pos);
		wsPos = line.find_first_of(" \t", pos);
	}
	std::string lastParam = line.substr(pos);
	if (lastParam.empty())
		return cp;
	pos = line.length();
	if (lastParam[0] != ':')
		cp.params.push_back(lastParam);
	else
		cp.trailing = lastParam.substr(1);
	
	return cp;
}

// void test_parser()
// {
//     std::cout << "=== TEST 1 : Avec prefix, commande, plusieurs params et trailing ===" << std::endl;
//     t_cmdParser cp1 = cmdParser(":nick!user@host PRIVMSG #channel :hello world");
//     std::cout << "Prefix: [" << cp1.prefix << "], Command: [" << cp1.command << "]" << std::endl;
//     std::cout << "Params: ";
//     for (size_t i = 0; i < cp1.params.size(); ++i) std::cout << "[" << cp1.params[i] << "] ";
//     std::cout << "\nTrailing: [" << cp1.trailing << "]\n" << std::endl;
    
//     std::cout << "=== TEST 2 : Avec prefix, commande, plusieurs params, sans trailing ===" << std::endl;
//     t_cmdParser cp2 = cmdParser(":nick PRIVMSG #channel arg1 arg2 arg3");
//     std::cout << "Prefix: [" << cp2.prefix << "], Command: [" << cp2.command << "]" << std::endl;
//     std::cout << "Params: ";
//     for (size_t i = 0; i < cp2.params.size(); ++i) std::cout << "[" << cp2.params[i] << "] ";
//     std::cout << "\nTrailing: [" << cp2.trailing << "]\n" << std::endl;
    
//     std::cout << "=== TEST 3 : Sans prefix, commande, plusieurs params et trailing ===" << std::endl;
//     t_cmdParser cp3 = cmdParser("PRIVMSG #channel nick1 nick2 :message avec espaces");
//     std::cout << "Prefix: [" << cp3.prefix << "], Command: [" << cp3.command << "]" << std::endl;
//     std::cout << "Params: ";
//     for (size_t i = 0; i < cp3.params.size(); ++i) std::cout << "[" << cp3.params[i] << "] ";
//     std::cout << "\nTrailing: [" << cp3.trailing << "]\n" << std::endl;
    
//     std::cout << "=== TEST 4 : Sans prefix, commande seule ===" << std::endl;
//     t_cmdParser cp4 = cmdParser("PING");
//     std::cout << "Prefix: [" << cp4.prefix << "], Command: [" << cp4.command << "]" << std::endl;
//     std::cout << "Params: ";
//     for (size_t i = 0; i < cp4.params.size(); ++i) std::cout << "[" << cp4.params[i] << "] ";
//     std::cout << "\nTrailing: [" << cp4.trailing << "]\n" << std::endl;
    
//     std::cout << "=== TEST 5 : Sans prefix, commande avec un seul param ===" << std::endl;
//     t_cmdParser cp5 = cmdParser("JOIN #channel");
//     std::cout << "Prefix: [" << cp5.prefix << "], Command: [" << cp5.command << "]" << std::endl;
//     std::cout << "Params: ";
//     for (size_t i = 0; i < cp5.params.size(); ++i) std::cout << "[" << cp5.params[i] << "] ";
//     std::cout << "\nTrailing: [" << cp5.trailing << "]\n" << std::endl;
    
//     std::cout << "=== TEST 6 : Avec prefix et commande, pas de params ===" << std::endl;
//     t_cmdParser cp6 = cmdParser(":server PONG");
//     std::cout << "Prefix: [" << cp6.prefix << "], Command: [" << cp6.command << "]" << std::endl;
//     std::cout << "Params: ";
//     for (size_t i = 0; i < cp6.params.size(); ++i) std::cout << "[" << cp6.params[i] << "] ";
//     std::cout << "\nTrailing: [" << cp6.trailing << "]\n" << std::endl;
// }