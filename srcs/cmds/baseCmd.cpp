/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   baseCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 16:20:46 by agouin            #+#    #+#             */
/*   Updated: 2026/06/01 16:26:19 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/base.hpp"


BaseCmd::BaseCmd(std::string line)
{
	(void)line;
		//a faire
}

std::string BaseCmd::getCmdName(void)
{
	return(this->cmd_name);
}

std::string BaseCmd::getRaw(void)
{
	return(this->Raw);
}


std::vector<std::string> BaseCmd::getVector(void)
{
	return (this->cmdVector);
}	
	
//void	write(std::string msg){std::cout << CYAN << "Command " + cmd_name + " : "+ WHI + msg << std::endl;}
//{
	
//}