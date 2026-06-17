/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:12:19 by skuor             #+#    #+#             */
/*   Updated: 2026/06/17 14:59:00 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bot.hpp"

Bot::Bot(std::string ip, int port, std::string password) : _ip(ip), _port(port), _password(password)
{
	this->_loadBannedWords();
}

Bot::~Bot() {}

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

void	Bot::sendMsg(std::string msg)
{
	std::string	newMsg = msg;

	newMsg += "\r\n";
	size_t	fullSize = newMsg.size();
	size_t	sent = 0;
	
	while (sent < fullSize)
	{
		ssize_t n = send(_fd, newMsg.c_str() + sent, fullSize - sent, 0);
		if (n == -1)
			throw Exception("Error: send failed");
		sent += n;
	}
}

void	Bot::registerBot()
{
	std::string passMsg = "PASS " + _password;
	std::string	nickMsg = "NICK Bot";
	std::string userMsg = "USER Bot 0 * :Bot Censor";

	_write("Sending PASS, NICK and USER");
	sendMsg(passMsg);
	sendMsg(nickMsg);
	sendMsg(userMsg);
}

t_botParser	Bot::_parsingLine(std::string line)
{
	//:nick!user@host PRIVMSG #channel :contenu du message

	//:nick!user@host JOIN #channel
	t_botParser	bp;
	size_t pos = 0;
	size_t wsPos = 0;

	if (line.empty())
		return bp;

	if (line[0] == ':')
	{
		std::string prefix;
		wsPos = line.find_first_of(" \t", 0);
		if (wsPos != std::string::npos)
		{
			prefix = line.substr(1, wsPos - 1);
			pos = prefix.find('!');
			if (pos != std::string::npos)
			{
				bp.nick = prefix.substr(0, pos);
				pos = wsPos + 1;

			}
			else
				pos = wsPos + 1;
		}
	}

	pos = skip_ws(line, pos);

	wsPos = line.find_first_of(" \t", pos);
	if (wsPos != std::string::npos)
	{
		bp.command = line.substr(pos, wsPos - pos);
		pos = wsPos + 1;
	}
	else
	{
		bp.command = line.substr(pos);	
		pos = line.length();
	}

	pos = skip_ws(line, pos);
	wsPos = line.find_first_of(" \t", pos);
	if (wsPos != std::string::npos)
	{
		size_t findHashtag = line.find('#', pos);
		if (findHashtag == std::string::npos)
			return bp;
		bp.channel = line.substr(findHashtag);
		pos = wsPos + 1;
	}
	else
	{
		size_t findHashtag = line.find('#', pos);
		if (findHashtag == std::string::npos)
			return bp;
		bp.channel = line.substr(findHashtag);
	}
	
	pos = skip_ws(line, pos);
	size_t findMsg = line.find(':', pos);
	if (findMsg != std::string::npos)
		bp.msg = line.substr(findMsg + 1);

	return bp;
}

void	Bot::_loadBannedWords()
{
	std::string	line;
	_srcFile.open("bot/bannedWords.txt");
	if (!_srcFile.is_open())
	{
		std::cerr << "Unable to open file" << std::endl;
		return ;
	}
	if (_srcFile.peek() == EOF)
	{
		std::cerr << "File is empty" << std::endl;
		return ;	
	}
	while (getline(_srcFile, line))
	{
		if (line.empty())
			continue ;
		_bannedWords.push_back(line);
	}
}

void	Bot::handleLine(std::string line)
{
	_write("Received: " + line);

	t_botParser bp = _parsingLine(line);
	// _write("command: [" + bp.command + "]");
	// _write("channel: [" + bp.channel + "]");
	// _write("nick: [" + bp.nick + "]");
	// _write("msg: [" + bp.msg + "]");
	
	if (bp.command == "PING")
	{
		std::string pingMsg = "PONG " + bp.msg;
		_write("PONG sent");
		sendMsg(pingMsg);
	}
	if (bp.command == "JOIN")
	{   
		_channel = bp.channel;
		_write("joined the channel " + _channel);
		std::string joinMsg = "JOIN " + _channel;
		sendMsg(joinMsg);
	}
	// if (bp.command == "INVITE")
	// {   
	// 	_channel = bp.channel;
	// 	_write("joined the channel " + _channel);
	// 	std::string joinMsg = "JOIN " + _channel;
	// 	sendMsg(joinMsg);
	// }
	// if (bp.command == "475")
	// {
	// 	_write("Cannot JOIN the channel: +k");
	// 	_channel = "";
	// }
	// if (bp.command == "366")
	// {
	// 	_write("Asked for operator status");
	// 	std::string msg = "PRIVMSG " + _channel + " :[BOT] Hello! Please give me operator status with /mode #chan +o Bot";
	// 	sendMsg(msg);
	// }
	if (bp.command == "PRIVMSG")
	{		
		std::vector<std::string>::iterator it;
		for (it = _bannedWords.begin(); it != _bannedWords.end(); ++it)
		{
			size_t pos = bp.msg.find(*it);
			if (pos != std::string::npos)
			{
				_warnings[bp.nick]++;
				
				if (_warnings[bp.nick] == 1)
				{
					_write("1st warning sent");
					std::string firstWarn = "PRIVMSG " + _channel + " :[BOT] " + bp.nick + ", this is your first warning. Keep it clean.";
					sendMsg(firstWarn);
				}
				else if (_warnings[bp.nick] == 2)
				{
					_write("2nd warning sent");
					std::string secondWarn = "PRIVMSG " + _channel + " :[BOT] " + bp.nick + ", this is your last warning before being kicked.";
					sendMsg(secondWarn);
				}
				else if (_warnings[bp.nick] > 2)
				{
					_write("Kicked " + bp.nick);
					std::string kickMsg = "KICK " + _channel + " " + bp.nick + " :You have been kicked for using banned words.";
					sendMsg(kickMsg);
					_warnings[bp.nick] = 0;
				}
				break ;
			}
		}
	}
}


void	Bot::_write(std::string msg)
{
	std::cout << YELLOW << "[Bot] " << DEFAULT << msg << std::endl;
}
