#ifndef _WASTE_HPP_
#define _WASTE_HPP_

#include "main.hpp"
#include "card.hpp"

class waste
{
	protected:
		card* first;
		card* current;
	
	public:
		card* get_first()	{return first;}
		card* get_current()	{return current;}
	
		card* remove_current(); 
		void next(bool three);
};

#endif