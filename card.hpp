#ifndef _CARD_HPP_
#define _CARD_HPP_
#include <stdbool.h>
#include <string> 
#include <stdint.h>

class card
{
	public:
		uint8_t id:6;
		bool visible	:1;

	public:
		bool get_visible(){return visible;}
		bool get_color();
		uint8_t get_number();
		uint8_t get_symbol();
		std::string show_card();
};

#endif