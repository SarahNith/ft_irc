/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:37:36 by skuor             #+#    #+#             */
/*   Updated: 2026/06/05 16:43:36 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "../../includes/base.hpp"

class Channel {
	public:
		Channel();
		Channel(Client* client, std::string name);
		~Channel();

		std::string	getName() const;
		std::string	getTopic() const;
		// std::string	getMode() const;
		std::string	getChannelKey() const;
		size_t		getCapacityLimit() const;
		bool		isInviteOnly() const;
		bool		hasTopicRestriction() const;
		
		std::vector<Client*>	getOpe() const;
		std::vector<Client*>	getMembers() const;
		std::vector<Client*>	getInviteList() const;

		void	write(const std::string & msg);

		void	setName(std::string newName);
		void	setTopic(std::string newTopic);
		// void	setMode(std::string newMode);
		void	setKey(std::string newKey);
		void	setLimitCapacity(size_t limit);
		void	setInviteOnly(bool isInviteOnly);
		void	setTopicRestriction(bool hasTopRestriction);
		
		void	addMember(Client* member);
		void	removeMember(Client* member);
		void	addOpe(Client* ope);
		void	removeOpe(Client* ope);
		void	addToInviteList(Client* invited);
		void	removeFromInviteList(Client* member);
		
		bool	isMember(Client* client);
		bool	isOpe(Client* client);
		bool	isInvited(Client* client);
		
	private:

		typedef struct s_modes {
			
			bool		inviteOnly;
			bool		topicRestriction;
			std::string	key;
			size_t		limit;
		
		}	t_modes;
	
		std::string	_name;
		std::string	_topic;
		// std::string	_mode;
		// std::string	_channelKey;
		// size_t	_capacityLimit;

		
		t_modes		_chanModes;
				
		std::vector<Client*>	_operators;
		std::vector<Client*>	_members;
		std::vector<Client*>	_inviteList;


		
};


#endif

//MODES
// · i: Set/remove Invite-only channel
// · t: Set/remove the restrictions of the TOPIC command to channel operators
// · k: Set/remove the channel key (password)
// · o: Give/take channel operator privilege
// · l: Set/remove the user limit to channel