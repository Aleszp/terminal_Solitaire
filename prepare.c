#include "core.h"

//Tworzy talię, tasuje ją i szykuje rozdanie
void deal(card_list* waste_begin, card_list* waste,card *const tableau)
{
	//char *tmp;
	card talia[52];
	//stwórz talię 52 kart
	for(unsigned i=0;i<52;i++)
	{
		talia[i].id=i+1;
		talia[i].visible=1;
		talia[i].chosen=0;
	}
	//połóż 24 losowe karty na stos
	for(int i=0;i<24;i++)
	{
		unsigned char los;
		do
		{
			los=losowa(52);
		}
		while(talia[los].id==0);
		
		add_to_waste(waste,talia+los);
		waste=waste->next;
	}
	waste=waste_begin;
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

}

void umiesc(card *const to, card *const from, bool visible)
{
	to->id=from->id;
	from->id=0;
	to->visible=visible;
}

//zwraca losową liczbę całkowitą mniejszą od liczby "max"
int losowa(int max){return rand()%max;}

card_list* create_waste()
{
	card_list* waste_begin=(card_list*)malloc(sizeof(card_list)); //i=0
	card_list *tmp1, *tmp2;
	tmp1=waste_begin;
	tmp1->prev=NULL;
	for(unsigned char i=1;i<24;i++) //i=1, bo już stworzono i=0
	{
		tmp2=(card_list*)malloc(sizeof(card_list));
		tmp1->next=tmp2;
		tmp2->prev=tmp1;
		tmp1=tmp2;
	}
	tmp1->next=NULL;
	
	return waste_begin;
}

void add_to_waste(card_list *const waste,card *const from)
{
	waste->karta.id=from->id;
	from->id=0;
	waste->karta.visible=true;
}