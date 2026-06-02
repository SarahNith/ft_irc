/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:32 by agouin            #+#    #+#             */
/*   Updated: 2026/06/02 15:12:52 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/base.hpp"

static bool	isWhitespace(char ws)//a mettre ailleur Sarah la deja fait
{
	if (ws == ' ' || ws == '\t')
		return true;
	return false;
}

static size_t	skip_ws(std::string line, size_t i)//a mettre ailleur Sarah la deja fait
{
	while (i < line.length() && isWhitespace(line[i]))
		i++;
	return (i);
}

int is_port_correct(std::string str)//continuer il faut juste voir si pas une string decoupe et bien dans le chanp 
{
	if (str.empty() || skip_ws(str, 0) == str.length())
		return (-1);
	for (size_t i = 0; i < str.length(); i++)
	{
		if (std::isdigit(str[i]) == false)
			return (-1);
	}
}

std::string obtainPort(std::string str)
{
	std::string port;
//ici je veux recuperer la string valide comme ca je lenvoie dans le server au leiu de argv qui est plus problematique 
	
}

int main(int argc, char **argv)//peut etre env si on veut avoir lheure
{
	if(argc != 3 || is_port_correct(argv[1]) == -1)
	{
		std::cout << RED << "Wrong Executable : " <<  DEFAULT BOLD << "./ircserv <port> <password>" << DEFAULT << std::endl;
		return (-1);
	}
	//vérification du port entre 1 et 65535 vérifier
	try
	{
		Server serv(atoi(argv[1]), argv[2]);
		serv.run_server();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}

//plusieurs connexions avant davoir "Error : Recv failed"
