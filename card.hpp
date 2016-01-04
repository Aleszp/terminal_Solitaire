#ifndef _CARD_HPP_
#define _CARD_HPP_
#include <stdbool.h>
#include <string> 

class card
{
	public:
		unsigned char id:6;
		bool visible	:1;

	public:
		bool get_Visible(){return visible;}
		bool get_Color();
		unsigned char get_Number();
		unsigned char get_Symbol();
		std::string show_Card();
};

#endif