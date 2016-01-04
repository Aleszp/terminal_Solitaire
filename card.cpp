#include "card.hpp"
#include "main.hpp"
#include <string> 

using namespace std;

bool card::get_Color()
{
	if(get_Symbol()==HEARTS||get_Symbol()==DIAMONDS)
		return RED;
	return BLACK;
}

unsigned char card::get_Number()
{
	return id%13;
}

unsigned char card::get_Symbol()
{
	//1-13 - ♥, 14-26 - ♣, 27-39 - ♦, 40-52 - ♠
	return (id-get_Number())/13;
}

string card::show_Card()
{
	string desc("      ");
	switch (get_Symbol())
	{
		case HEARTS:
			desc=" ♥";
		break;
		case CLUBS:
			desc=" ♣";
		break;
		case DIAMONDS:
			desc=" ♦";
		break;
		case SPADES:
			desc=" ♠";
		break;
	}
	switch(get_Number())
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
			desc+=get_Number()+" ";
	}
	
	return desc;
}