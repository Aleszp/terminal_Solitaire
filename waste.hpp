#ifndef _WASTE_HPP_
#define _WASTE_HPP_

#include "main.hpp"
#include "card.hpp"

class waste
{
	protected:
		card* first;
		card* current;
		card* third;
	
	public:
		card* get_first()	{return first;}
		card get_current_id()	{return current->id;}
	
		card* remove_current(); 
		void next(bool three_);
		void show(bool three_);
		void update_third_ptr();
};

#endif