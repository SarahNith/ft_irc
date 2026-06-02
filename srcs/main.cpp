/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:32 by agouin            #+#    #+#             */
/*   Updated: 2026/06/02 15:48:05 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/base.hpp"

int main(int argc, char **argv)//peut etre env si on veut avoir lheure
{
	if(argc != 3)
		return (-1);
	//vérification du port entre 1 et 65535 vérifier
	try
	{
		Server serv(atoi(argv[1]), argv[2]);
		serv.run_server();
		test_parser();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}