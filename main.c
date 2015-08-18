#include "core.h"

int main(void)
{
	srand (time (NULL));
	bool play=true;
	bool game=true;
	bool three=true; //if true than cards will be dealt in groups of three, otherwise one at a time
	card_list* waste_begin=create_waste();
	card_list* waste;
	card tableau[140];
	card foundation[52];
	int score;
	unsigned rozdania=0;
	unsigned char decision;
	
	if (!setlocale(LC_CTYPE, "")) 
	{
        fprintf(stderr, "Cannot set locale\n");
        return 1;
    }
	
	//w tej pętli trwa gra dopóki gracz jej nie zakończy, w razie wygranej umożliwia rozpoczęcie kolejnego rozdania
	do
	{
		//opróżnij stosiki
		for(card *wsk=tableau;wsk!=tableau+139;wsk++)
		{
			wsk->id=0;
			wsk->visible=true;
			wsk->chosen=false;
		}
		//opróżnij komórki
		for(card *wsk=foundation;wsk!=foundation+52;wsk++)
		{
			wsk->id=0;
			wsk->visible=true;
			wsk->chosen=false;
		}
		//ustaw wartości domyślne zmiennych
		score=0;
		rozdania=0;
		waste=waste_begin;
		game=true;
		//deal cards
		deal(waste_begin,waste, tableau);
		waste=NULL;
		
		//w tej pętli graczowi wyświetlane są karty i opcje, gracz wybiera akcje
		do
		{
			//wypisz karty
			show_cards(waste, tableau, foundation, score, three);
			
			//pozwól wybrać graczowi co robić
			decision=decide();
			
			switch(decision)
			{
				case 1:
				 
				break;
				case 2:
					deal_next(&waste, waste_begin, &rozdania, &score,three); //deal next cards?
				break;
				case 3:
					game=false; //new game?
				break;
				case 4:
					settings(&three, &game); //change settings?
				break;
				case 5:
					play=false; //end of game?
				break;
				default:
					fprintf(stdout,"Komenda nierozpozna.\n");
			}
		}
		while(play&&game); //czy rozdanie trwa?
	}
	while(play); //czy gracz chce jeszcze grać?
	
	return 0;
}
