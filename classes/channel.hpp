/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:37:36 by skuor             #+#    #+#             */
/*   Updated: 2026/05/28 15:07:02 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "../includes/base.hpp"

class Channel {
	public:
		Channel(Client* client, std::string name);
		~Channel();

		std::string	getName() const;
		std::string	getTopic() const;
		std::string	getMode() const;
		std::string	getChannelPassword() const;
		int			getCapacityLimit() const;

		void	write(const std::string & msg);

		void	setName(std::string newName);
		void	setTopic(std::string newTopic);
		void	setMode(std::string newMode);
		void	setPassword(std::string newPassword);

		void	addMember(Client* member);
		void	removeMember(Client* member);
		void	addOpe(Client* ope);
		void	removeOpe(Client* ope);

		bool	isMember(Client* client);
		bool	isOpe(Client* client);		

		
	private:
		std::string	_name;
		std::string	_topic;
		std::string	_mode;
		std::string	_channelPassword;
		
		std::vector<Client*>	_operators;
		std::vector<Client*>	_members;

		int	_capacityLimit;
};


#endif