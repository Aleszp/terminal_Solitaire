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
	
	//1 - Ace, 11 -Jack, 12 - Queen, 0 - King
	opis[1]=card_sign(card_color(karta));
	
	switch (card_value(karta)) //checks card value
	{
		case ACE:
			opis[2]=L'A';
		break;
		case 10:
			opis[2]=L'1';
			opis[3]=L'0';
		break;
		case JACK:
			opis[2]=L'J';
		break;
		case QUEEN:
			opis[2]=L'Q';
		break;
		case KING:
			opis[2]=L'K';
		break;
		default:
			opis[2]=L'0'+card_value(karta);
	}
	return opis;
}

unsigned char card_value(card *const karta)
{
	return karta->id%13;
}
unsigned char card_color(card *const karta)
{
	return ((karta->id%13)==0?(((karta->id)/13)-1):(((karta->id)-(karta->id)%13))/13);
}
wchar_t card_sign(unsigned char color)
{
	wchar_t tmp=L'!';
	switch(color) //♥♣♦♠
	{
		case HEARTS:
			tmp=L'\u2665';
		break;
		case CLUBS:
			tmp=L'\u2663';
		break;
		case DIAMONDS:
			tmp=L'\u2666';
		break;
		case SPADES:
			tmp=L'\u2660';
		break;
		default:
			tmp=L'!';
	}
	return tmp;
}

//shows cards
void show_cards(card_list *const waste, card_list *waste_end, card *const tableau, card *const foundation, unsigned wynik, bool three)
{
	fprintf(stdout,"TALIA:     ");
	
	wchar_t *tmp;
	
	//show waste
	if(waste!=NULL)
	{
		//show three/one card from waste
		for(card_list *wsk=waste;wsk!=waste_end->next;wsk=wsk->next)
		{
			if(wsk==waste_end)
			{
				wsk->karta.chosen=1;
			}
			tmp=describe(&(wsk->karta),wsk->karta.chosen);
			fprintf(stdout,"%ls",tmp);
			free(tmp);
			
			/*if((wsk->next!=NULL))
				wsk=wsk->next;
			else
				break;*/
		}
	}
	else
	{
		fprintf(stdout,"XX");
	}
	
	//show tableau
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
	
	//show foundation:
	for(unsigned char j=0;j<4;j++)
	{
		fprintf(stdout,"\nKOMÓRKA %lc: ",card_sign(j));
		for(unsigned char k=0;k<13;k++)
		{
			tmp=describe(&(foundation[13*j+k]),0);
			fprintf(stdout,"%ls",tmp);
			free(tmp);
		}
	}
	//tell score
	fprintf(stdout,"\nWYNIK:      %i punktów\n",wynik);
}

//Pozwala graczowi wybrać operację (przełóż kartę - 1 ,rozdaj trzy kolejne karty - 2, nowe rozdanie - 3, koniec gry - 4, nieznany wybór - 0)
unsigned char decide()
{
	char tmp[2]; //two-sign buffer, could have read only integers, but this way is more idiot-proof
	
	fprintf(stdout,"OPCJE DO WYBORU: 1 - przełóż kartę , 2 - rozdaj kolejne karty, 3 - karta do komórki, 4 - nowe rozdanie, 5 - opcje, 6 - koniec gry\nWYBÓR: ");
	scanf("%1s", tmp);
	if(!strcmp(tmp,"1"))return 1;
	if(!strcmp(tmp,"2"))return 2;
	if(!strcmp(tmp,"3"))return 3;
	if(!strcmp(tmp,"4"))return 4;
	if(!strcmp(tmp,"5"))return 5;
	if(!(strcmp(tmp,"6")&&strcmp(tmp,"q")&&strcmp(tmp,"Q")))return 6;
	return 0;
}

void deal_next(card_list **waste, card_list **waste_end,card_list *const waste_begin, unsigned *const rounds, int *const score, bool three)
{
	card_list *tmp=*waste;
	
	if(tmp==NULL)
	{
		tmp=waste_begin;
		(*rounds)++;
		if(*rounds>(three?3:1))
			*score-=(three?20:100);
		*waste=tmp;
		refresh_waste_pointer(waste, waste_end, three);
		
		return;
	}
	
	if((*waste_end)->next==NULL)
	{
		*waste=NULL;
		*waste_end=NULL;
		return;
	}
	
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
	*waste=tmp;	
	refresh_waste_pointer(waste, waste_end, three);
}

void refresh_waste_pointer(card_list **waste, card_list **waste_end, unsigned char many)
{
	(*waste_end)=(*waste);
	if(*waste_end==NULL)
		return;
	if(many<2)
		return;
	for(unsigned char i=0;i<many-1;i++)
	{
		if((*waste_end)->next!=NULL)
		{
			(*waste_end)=(*waste_end)->next;
		}
		else
			return;
	}
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

card *remove_from_waste(card_list **waste)
{
	card *tmp=malloc(sizeof(card));
	card_list *pointer=*waste;
	if(waste==NULL) //is waste empty?
	{
		//generate dummy card
		tmp->id=0;
		tmp->visible=true;
		tmp->chosen=false;
	}
	else
	{	
		tmp->id=pointer->karta.id;
		tmp->visible=true;
		tmp->chosen=false;
		(*waste)=(*waste)->prev;
		
		//free memory
		(*waste)->next=pointer->next;
		(*waste)->karta.chosen=0;
		free(pointer);
		pointer=(*waste)->next;
		pointer->prev=(*waste);
	}
	return tmp;
}

bool may_add_to_tableau(card *const karta, card *const tableau, unsigned char tableau_id)
{
	//is there even any card to move?
	if(karta==NULL||karta->id==0)
	{
		fprintf(stdout,"Brak karty do przełożenia\n");
		return false;
	}
	
	//prepare temporaty pointer
	card *tmp=tableau+20*tableau_id;
	
	//is this card a king?
	if((card_value(karta)==KING))
	{
		//is this place empty?
		if(tmp->id==0)
			return true;
		else
		{
			fprintf(stdout,"Króla można położyć wyłącznie na pustym polu.\n");
			return false;
		}
	}
	//for any other card
	
	//move pointer to top card
	while(((tmp+1)->id!=0)&&(tmp-(tableau+20*tableau_id)<20)) //if tebleau is full also deny
		tmp++;
	//is this card visible?
	if(!tmp->visible)
	{
		fprintf(stdout,"Nie można położyć na nieznanej karcie.\n");
		return false;
	}
	//do we want to put anything on ace?
	if(card_value(tmp)==ACE)
	{
		fprintf(stdout,"Żadnej karty nie można położyć na asie.\n");
		return false;
	}
	//are we trying to put on king something else than queen?
	if(card_value(tmp)==KING&&card_value(karta)!=QUEEN)
	{
		fprintf(stdout,"Kartę można położyć tylko na karcie z wartością o jeden większą.\n");
		return false;
	}
	//are we trying tu put card with number not being ONE lower than card on which we put it? 
	if(((card_value(tmp)-1)!=card_value(karta))&&(card_value(tmp)!=KING&&card_value(karta)!=QUEEN))
	{
		fprintf(stdout,"Kartę można położyć tylko na karcie z wartością o jeden większą.\n");
		return false;
	}
	//are colors the same (both red or both black)?
	if(card_color(tmp)%2==card_color(karta)%2)
	{
		fprintf(stdout,"Kartę można położyć tylko, jeśli mają różne kolory.\n");
		return false;
	}
	return true;
}

unsigned char choose_tableau()
{
	char tmp[2]; //two-sign buffer, could have read only integers, but this way is more idiot-proof
	fprintf(stdout,"Który stosik?\nWYBÓR: ");
	scanf("%1s", tmp);
	if(!strcmp(tmp,"1"))return 1;
	if(!strcmp(tmp,"2"))return 2;
	if(!strcmp(tmp,"3"))return 3;
	if(!strcmp(tmp,"4"))return 4;
	if(!strcmp(tmp,"5"))return 5;
	if(!strcmp(tmp,"6"))return 6;
	if(!strcmp(tmp,"7"))return 7;
	return 0;
}


void add_to_tableau(card *const karta, card *const tableau, unsigned char tableau_id)
{
	//prepare temporaty pointer
	card *tmp=tableau+20*tableau_id;
	//move pointer to top card
	while(((tmp)->id!=0)&&(tmp-(tableau+20*tableau_id)<20)) //if tebleau is full also deny
		tmp++;
	tmp->id=karta->id;	//copy card value
	tmp->visible=1;		//make visible
	tmp->chosen=0;		//it's not chosen
}

bool may_add_to_foundation(card *const karta, card *const foundation)
{
	card *pointer=foundation+karta->id-1;
	if(card_value(pointer-1)==0&&card_value(karta)!=1)
		return false;
	else
		return true;
}

void add_to_foundation(card *const karta, card *const foundation)
{
	card *pointer=foundation+karta->id-1;
	
	pointer->id=karta->id;
	pointer->visible=1;
	pointer->chosen=0;
	
	karta->id=0;
	karta->visible=1;
	karta->chosen=0;
}

bool may_remove_many_from_tableau(card *const tableau, unsigned char tableau_id, unsigned char card_id)
{
	card *pointer=tableau+20*tableau_id+card_id;
	for(unsigned char i=0;i<20;i++)
	{
		if(card_value(pointer+1)==0||i==20)	//nothing above/end of tableau?
			break;
		if(card_value(pointer)-card_value(pointer+1)!=1)	//if card above value isn't a one smaller -> can't move
			return false;
		if(card_color(pointer)%2-card_color(pointer+1)%2==0)	//if card colors doesn't differ -> can't move
			return false;
		pointer++;
	}
	
	return true;
}

card remove_many_from_tableau(card *const tableau, unsigned char tableau_id, bool remove)
{
	card tmp;
	card *pointer=tableau+20*tableau_id;
	for(unsigned char i=0;i<20;i++)
	{
		if(card_value(pointer+1)==0||i==20)	//nothing above/end of tableau?
			break;
		pointer++;
	}
	tmp.id=pointer->id;
	tmp.chosen=0;
	tmp.visible=1;
	if(remove)
	{
		pointer->id=0;
		pointer->chosen=0;
		pointer->visible=1;
		(pointer-1)->visible=1;
	}
	return tmp;
}

unsigned char where_from()
{
	char tmp[2]; //two-sign buffer, could have read only integers, but this way is more idiot-proof
	fprintf(stdout,"Skąd? \nOPCJE DO WYBORU: 0 - talia , 1 - 7 - stosik o danym numerze\nWYBÓR: ");
	scanf("%1s", tmp);
	if(!strcmp(tmp,"0"))return 0;
	if(!strcmp(tmp,"1"))return 1;
	if(!strcmp(tmp,"2"))return 2;
	if(!strcmp(tmp,"3"))return 3;
	if(!strcmp(tmp,"4"))return 4;
	if(!strcmp(tmp,"5"))return 5;
	if(!strcmp(tmp,"6"))return 6;
	if(!strcmp(tmp,"7"))return 7;
	return 10;
}

void move_many_in_tableau(card *const tableau, unsigned char tableau1_id, unsigned char tableau2_id, unsigned char card_id)
{
	card *from=tableau+20*tableau1_id+card_id;
	card *to=tableau+20*tableau2_id+card_id;
	
	card *tmp_from=tableau+20*tableau1_id+20;
	card *tmp_to=tableau+20*tableau2_id+20;
	
	while(to->id!=0&&to!=tmp_to)
		to++;
	while(from->id!=0&&from!=tmp_from&&to!=tmp_to)
	{
		to->id=from->id;
		from->id=0;
		to->visible=1;
		to->chosen=0;
		from->chosen=0;
		to++;
		from++;
	}
}