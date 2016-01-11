#ifndef _TABLEAU_HPP_
#define _TABLEAU_HPP_

#include "card.hpp"
#include "main.hpp"

class tableau
{
	protected:
		card *pile[7];
	
	public:
		void show();
};

#endif