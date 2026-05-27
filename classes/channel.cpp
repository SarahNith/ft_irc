/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:09:02 by agouin            #+#    #+#             */
/*   Updated: 2026/05/27 14:20:45 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/base.hpp"


Channel::Channel()
{
}


Channel::Channel(const Channel& src)
{
	*this = src;
}
	

Channel &Channel::operator=(const Channel& src)
{
	if (this != &src)
	{

	}
	return (*this);
}


Channel::~Channel()
{
}