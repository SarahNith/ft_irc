#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "../includes/base.hpp"

class	Channel 
{
	public :

		Channel();
		Channel(const Channel &src);
		Channel &operator=(const Channel &src);
		~Channel();

};

#endif