/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:00:32 by agouin            #+#    #+#             */
/*   Updated: 2026/05/29 12:04:46 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "../includes/base.hpp"

int main(int argc, char **argv)//peut etre env si on veut avoir lheure
{
	// if(argc != 3)
	// 	return (-1);
	// Server serv(argv[1], argv[2]);
	(void)argc;
	(void)argv;
	test_parser();
	
	return (0);
}