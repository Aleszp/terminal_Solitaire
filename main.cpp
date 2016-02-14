#include "main.hpp"
#include "card.hpp"
#include "card_deck.hpp"
#include "foundation.hpp"
#include "tableau.hpp"
#include "waste.hpp"

#include <iostream>

void print_version(void){cout<<"Pasjans konsolowy, autor: Aleksander Szpakiewicz-Szatan. \nWersja: C++pre-alfa3"<<endl;}

int main(void)
{
	srand (time (NULL));
	
	card_deck deck;
	bool playing=true;
	bool game=true;
	bool three=true; //rozdawać 3 czy 1 kartę?
	unsigned decision;
	
	while(playing)
	{
		game=true;
		cout<<"Rozpoczynam nowe rozdanie."<<endl;
		
		deck.~card_deck();	//zwolnij pamięć
		deck=card_deck();	//potasuj nowe karty
		deck.reset_waste_current();
		
		while(game)
		{
			deck.show_cards(three);
			decision=deck.get_decision();
			switch(decision)
			{
				case MOVE_CARD:
					
				break;
				case NEXT_CARD:
					deck.next_card(three);
				break;
				
				break;
				case NEW_GAME:
					game=false;
				break;
				case END_GAME:
					game=false;
					playing=false;
				break;
				case NONE:
					
				break;
			}
		}
	}
	
	return 0;
}



