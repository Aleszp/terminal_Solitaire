#include "core.h"

//zwraca opis karty: [znak odstępu], [symbol], [wartość cyfra 1], [wartość cyfra 2], [znak odstępu]
wchar_t *describe(card *const karta, bool wybrana)
{
	wchar_t *opis;
	unsigned char id=0;
	
	if(karta->id==0)
	{
		opis=(wchar_t*)malloc(sizeof(wchar_t));
		*opis='\0';
		return opis;
	}
	
	opis=(wchar_t*)malloc(6*sizeof(wchar_t));
	opis[id++]=wybrana?L'*':L' ';
	opis[id++]=L'?';
	opis[id++]=L'?';
	opis[id++]=wybrana?L'*':L' ';
	opis[id++]=wybrana?L'*':L' ';
	opis[id++]='\0';
	
	id=karta->id;
	
	if(karta->visible==false)
		return opis;
	
	unsigned char numer=id%13;
	//1 - As, 11 -Walet, 12 - Dama, 0 - Król
	
	switch(numer==0?id/13-1:(id-numer)/13) //♥♣♦♠
	{
		case 0:
			opis[1]=L'\u2665';
		break;
		case 1:
			opis[1]=L'\u2663';
		break;
		case 2:
			opis[1]=L'\u2666';
		break;
		case 3:
			opis[1]=L'\u2660';
		break;
		default:
			opis[1]=L'!';
	}
	
	switch (numer) //checks card value
	{
		case A:
			opis[2]=L'A';
		break;
		case 10:
			opis[2]=L'1';
			opis[3]=L'0';
		break;
		case J:
			opis[2]=L'J';
		break;
		case Q:
			opis[2]=L'Q';
		break;
		case K:
			opis[2]=L'K';
		break;
		default:
			opis[2]=L'0'+numer;
	}
	return opis;
}

//wypisuje trzy wierzchnie karty stosu, 
void show_cards(card_list *const waste, card *const tableau, card *const foundation, unsigned wynik, bool three)
{
	fprintf(stdout,"TALIA:     ");
	
	wchar_t *tmp;
	card_list *wsk=waste;
	
	if(waste!=NULL)
	{
		//Wypisz 3 karty z wierzchu stosu
		for(unsigned char i=0;i<(three?3:1);i++)
		{
			tmp=describe(&(wsk->karta),wsk->karta.chosen);
			fprintf(stdout,"%ls",tmp);
			free(tmp);
			
			if(wsk->prev!=NULL)
				wsk=wsk->prev;
			else
				break;
		}
	}
	else
	{
		fprintf(stdout,"XX");
	}
	
	//Wypisz zawartość stosików:
	for(unsigned char j=0;j<7;j++)
	{
		fprintf(stdout,"\nSTOSIK %i:  ",j+1);
		for(unsigned char k=0;k<20;k++)
		{
			tmp=describe(&(tableau[20*j+k]),0);
			fprintf(stdout,"%ls",tmp);
			free(tmp);
		}
	}
	
	//Wypisz zawartość komórek:
	for(unsigned char j=0;j<4;j++)
	{
		fprintf(stdout,"\nKOMÓRKA %i: ",j+1);
		for(unsigned char k=0;k<13;k++)
		{
			tmp=describe(&(foundation[13*j+k]),0);
			fprintf(stdout,"%ls",tmp);
			free(tmp);
		}
	}
	//Tells score
	fprintf(stdout,"\nWYNIK:      %i punktów\n",wynik);
}

//Pozwala graczowi wybrać operację (przełóż kartę - 1 ,rozdaj trzy kolejne karty - 2, nowe rozdanie - 3, koniec gry - 4, nieznany wybór - 0)
unsigned char decide()
{
	char tmp[2]; //two-sign buffer, could have read only integers, but this way is more idiot-proof
	
	fprintf(stdout,"OPCJE DO WYBORU: 1 - przełóż kartę , 2 - rozdaj kolejne karty, 3 - nowe rozdanie, 4 - opcje, 5 - koniec gry\nWYBÓR: ");
	scanf("%1s", tmp);
	if(!strcmp(tmp,"1"))return 1;
	if(!strcmp(tmp,"2"))return 2;
	if(!strcmp(tmp,"3"))return 3;
	if(!strcmp(tmp,"4"))return 4;
	if(!strcmp(tmp,"5"))return 5;
	return 0;
}

void deal_next(card_list **waste, card_list *const waste_begin, unsigned *const rounds, int *const score, bool three)
{
	card_list *tmp=*waste;
	if(tmp==NULL)
	{
		tmp=waste_begin;
		if(three)
			for(unsigned char i=0;i<2;i++)
			{	
				if(tmp->next==NULL)
					break;
				tmp=tmp->next;
			}
		(*rounds)++;
		if(*rounds>(three?3:1))
			*score-=(three?20:100);
	}
	else
	{	
		if(tmp->next==NULL)
			tmp=NULL;
		else
		{	
			for(unsigned char i=0;i<(three?3:1);i++)
			{
				if(tmp->next==NULL)
					break;
				tmp=tmp->next;
			}
		}
	}
	*waste=tmp;
}

//Lets user change settings
void settings(bool *three, bool *game)
{
	fprintf(stdout, "Aby rozdawać po jednej karcie wybierz 1, apy po trzy 3, dowolny inny wybór - bez zmian. \nZmiana trybu gry powoduje rozpoczęcie nowego rounds.\nWYBOR:");
	char tmp[2]; //two-sign buffer, could have read only integers, but this way is more idiot-proof
	scanf("%1s", tmp);
	if(!strcmp(tmp,"1"))
	{
		*three=false;
		*game=false;
	}
	if(!strcmp(tmp,"3"))
	{
		*three=true;
		*game=false;
	}
}
