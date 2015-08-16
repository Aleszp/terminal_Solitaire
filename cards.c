#include "cards.h"

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

//zwraca opis karty: [znak odstępu], [symbol], [wartość cyfra 1], [wartość cyfra 2], [znak odstępu]
wchar_t *opisz(card *const karta, bool wybrana)
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
void wypisz(card_list *const waste, card *const tableau, card *const foundation, unsigned wynik)
{
	fprintf(stdout,"TALIA:     ");
	
	wchar_t *tmp;
	card_list *wsk=waste;
	
	if(waste!=NULL)
	{
		//Wypisz 3 karty z wierzchu stosu
		for(unsigned char i=0;i<3;i++)
		{
			tmp=opisz(&(wsk->karta),0);
			fprintf(stdout,"%ls",tmp);
			free(tmp);
			
			if(wsk->next!=NULL)
				wsk=wsk->next;
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
			tmp=opisz(&(tableau[20*j+k]),0);
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
			tmp=opisz(&(foundation[13*j+k]),0);
			fprintf(stdout,"%ls",tmp);
			free(tmp);
		}
	}
	//Tells score
	fprintf(stdout,"\nWYNIK:      %i punktów\n",wynik);
}

//Pozwala graczowi wybrać operację (przełóż kartę - 1 ,rozdaj trzy kolejne karty - 2, nowe rozdanie - 3, koniec gry - 4, nieznany wybór - 0)
unsigned char wybor()
{
	char tmp[2]; //two-sign buffer, could have read only integers, but this way is more idiot-proof
	
	fprintf(stdout,"OPCJE DO WYBORU: 1 - przełóż kartę , 2 - rozdaj trzy kolejne karty, 3 - nowe rozdanie, 4 - koniec gry\nWYBÓR: ");
	scanf("%1s", tmp);
	if(!strcmp(tmp,"1"))return 1;
	if(!strcmp(tmp,"2"))return 2;
	if(!strcmp(tmp,"3"))return 3;
	if(!strcmp(tmp,"4"))return 4;
	return 0;
}

void deal_next(card_list *const waste, unsigned *const rozdania, int *const score)
{
	
}

void add_to_waste(card_list *const waste,card *const from)
{
	waste->karta.id=from->id;
	from->id=0;
	waste->karta.visible=true;
}

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