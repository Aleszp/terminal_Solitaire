#include "card_deck.hpp"
#include "main.hpp"

#include <iostream>
#include <stdlib.h>

void card_deck::show_cards(bool three_)
{
	wst.show(three_);
	
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
	card talia[52];
	for(unsigned i=0;i<52;i++)
	{
		talia[i].id=i+1;
		talia[i].visible=1;
	}
	//połóż 24 losowe karty na stos
	for(int i=0;i<24;i++)
	{
		unsigned char los;
		do
		{
			los=rand()%52;
		}
		while(talia[los].id==0);
		cerr<<i<<'\t'<<(unsigned)talia[los].id<<endl;
		wst_.add(talia[los]);
		talia[los]=0;
	}
	cerr<<"c"<<endl;
	/*
	//połóż na 7 slupach po tyle kart ile wynosi numer slupa, ostatnia z wierzchu karta jest widoczna
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<=i;j++)
		{
			unsigned char los;
			do
			{
				los=losowa(52);
			}
			while(talia[los].id==0);			
			umiesc(&(tableau[20*i+j]),talia+los,j==i ? true: false);
		}
	}
	*waste=NULL;
	*/
	
	found=found_;
	table=table_;
	wst=wst_;
	cerr<<"d"<<endl;
}

card_deck::~card_deck()
{
	wst.~waste();
}