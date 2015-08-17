#include "core.h"

int main(void)
{
	srand (time (NULL));
	bool play=true;
	card_list* waste_begin=create_waste();
	card_list* waste;
	card tableau[140];
	card foundation[52];
	int score;
	unsigned rozdania=0;
	unsigned char decyzja;
	
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
		}
		//opróżnij komórki
		for(card *wsk=foundation;wsk!=foundation+52;wsk++)
		{
			wsk->id=0;
			wsk->visible=true;
		}
		//ustaw wartości domyślne zmiennych
		score=0;
		rozdania=0;
		waste=waste_begin;
		//deal cards
		deal(waste_begin,waste, tableau);
		waste=NULL;
		
		//w tej pętli graczowi wyświetlane są karty i opcje, gracz wybiera akcje
		do
		{
			//wypisz karty
			wypisz(waste, waste_begin, tableau, foundation, score);
			
			//pozwól wybrać graczowi co robić
			decyzja=wybor();
			if(decyzja==0)
			{
				fprintf(stdout,"Komenda nierozpozna.\n");
				continue;
			}
			if(decyzja==3)break;	//nowe rozdanie?
			else if(decyzja==4)play=false;		//koniec gry?
			else if(decyzja==2)deal_next(&waste, waste_begin, &rozdania, &score); //czy gracz chce rozdać kolejne karty?
			//else przeloz();
		}
		while(play); //czy rozdanie trwa?
	}
	while(play); //czy gracz chce jeszcze grać?
	
	return 0;
}
