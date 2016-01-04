#include "card_deck.hpp"
#include "main.hpp"

#include <iostream>

void card_deck::show_cards()
{
	
}
unsigned char card_deck::get_decision()
{
	string tmp;
	
	cout<<"1 - przenieś kartę, 2 - rozdaj, 3 - nowe rozdanie, 4 - koniec gry"<<endl<<"Wybór: ";
	cin>>tmp;
	switch(tmp.at(0)) //bezpieczniejsze niż pobieranie od użytkownika int'a
			{
				case '1':
					return MOVE_CARD;
				case '2':
					return NEXT_CARD;
				case '3':
					return NEW_GAME;
				case '4':
					return END_GAME;
				default:
					return NONE;
			}
}

card_deck::card_deck()
{
	foundation found_;
	tableau table_;
	waste wst_;
	
	found=found_;
	table=table_;
	wst=wst_;
}

card_deck::~card_deck()
{
	
}