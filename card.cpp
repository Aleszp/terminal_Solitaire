#include "card.hpp"
#include "main.hpp"
#include <string> 
#include <cstdio> 
#include <sstream>

using namespace std;

bool card::get_color()
{
	if(get_symbol()==HEARTS||get_symbol()==DIAMONDS)
		return RED;
	return BLACK;
}

uint8_t card::get_number()
{
	return id%13;
}

uint8_t card::get_symbol()
{
	//1-13 - ♥, 14-26 - ♣, 27-39 - ♦, 40-52 - ♠
	return id<52?(id-get_number())/13:SPADES;
}

string card::show_card()
{
	string desc("        ");
	switch (get_symbol())
	{
		case HEARTS:
			desc=" ♥"; //♥
		break;
		case CLUBS:
			desc=" ♣"; //♣
		break;
		case DIAMONDS:
			desc=" ♦"; //♦
		break;
		case SPADES:
			desc=" ♠"; //♠
		break;
	}
	switch(get_number())
	{
		case JACK:
			desc+="J ";
		break;
		case QUEEN:
			desc+="Q ";
		break;
		case KING:
			desc+="K ";
		break;
		default:
			char tmp[4];
			sprintf(tmp,"%u ",get_number());
			desc+=tmp;
	}
	
	return desc;
}