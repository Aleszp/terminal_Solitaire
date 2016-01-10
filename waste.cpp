#include "waste.hpp"

card* waste::remove_current()
{
	if(current==first)
		first=first->below;
	if(current->below!=NULL)
		(current->below)->above=current->above;
	if(current->above!=NULL)
		(current->above)->below=current->below;
	current->above=NULL;
	current->below=NULL;
	return current;
}

void waste::next(bool three)
{
	for(uint8_t i=three?1:3;i>0;i++)
	{
		if(current->below!=NULL)
			current=current->below;
		else
			current=first;
	}
}