#ifndef _WASTE_HPP_
#define _WASTE_HPP_

class waste
{
	protected:
		card *first;
		card *current;
	
	public:
		card *get_first()	{return first;}
		card *get_current()	{return current;}
	
		
};

#endif