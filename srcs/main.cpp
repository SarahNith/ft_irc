/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:32 by agouin            #+#    #+#             */
/*   Updated: 2026/06/03 14:58:19 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/base.hpp"


std::string obtainport(std::string str)
{
	size_t beg = 0;
	size_t end = str.size();
	
	while(beg < str.size() && ((str[beg] == 32) || str[beg] == 9))
		beg++;

	while(end > 0 && ((str[end] == 32) || str[end] == 9))
		end--;
	return (str.substr(beg, end - beg));
}


int is_port_correct(std::string str)
{
	int c = 0;
	if (str.empty())//+ verirfier nb port
		return (-1);

	for(size_t i = 0; i < str.size(); i++)
	{
		if (c == 1 && ((str[i] != 32) && str[i] != 9))
			return (-1);
		if (std::isdigit(str[i]) == true && ((str[i + 1] == 32) || str[i + 1] == 9))
			c = 1;
		if (std::isdigit(str[i]) == false && ((str[i] != 32) && str[i] != 9))
			return (-1);
	}
	int at = atoi(obtainport(str).c_str());
	if (at <= 0 || at >= 65535) //voir si on prend ces ports
		return (-1);
	return (0);
}


int main(int argc, char **argv)//peut etre env si on veut avoir lheure
{
	if(argc != 3 || is_port_correct(argv[1]) == -1)
	{
		std::cout << RED << "Wrong Executable : " <<  DEFAULT BOLD << "./ircserv <port> <password>" << DEFAULT << std::endl;
		return (-1);
	}
	try
	{
		Server serv(atoi(obtainport(argv[1]).c_str()), argv[2]);
		serv.run_server();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}

//plusieurs connexions avant davoir "Error : Recv failed"
