/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 17:50:13 by skuor             #+#    #+#             */
/*   Updated: 2026/06/17 11:29:42 by skuor            ###   ########.fr       */
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
	cp.hasTrailing = false;
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
			cp.hasTrailing = true;
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
	{
		cp.trailing = lastParam.substr(1);
		cp.hasTrailing = true;
	}
	return cp;
}

std::vector<std::string>	parsingParam(std::string param)
{
	std::vector<std::string>	paramVec;

	size_t commaPos = param.find(',');
	while (commaPos != std::string::npos)
	{
		paramVec.push_back(param.substr(0, commaPos));
		param = param.substr(commaPos + 1);
		commaPos = param.find(',');
	}
	paramVec.push_back(param);
	return paramVec;
}
