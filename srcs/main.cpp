/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:32 by agouin            #+#    #+#             */
/*   Updated: 2026/05/26 12:27:21 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "../includes/base.hpp"

int main(int argc, char **argv)//peut etre env si on veut avoir lheure
{
	if(argc != 3)
		return (-1);
	//vérification du port entre 1 et 65535 vérifier
	Server serv(std::atoi(argv[1]), argv[2]);
	serv.run_server();
	return (0);
}