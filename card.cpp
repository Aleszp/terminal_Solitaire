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
	string desc;
	if(!visible)
		return(" XX ");
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

card::card(uint8_t id_, bool visible_)
{
	id=id_;
	visible=visible_;
	above=NULL;
	below=NULL;
}

void card::show_line()
{
	card *tmp=this;
	
	while(tmp->below!=NULL)
	{
		cout<<(tmp->show_card());
		tmp=tmp->below;
	}
}	