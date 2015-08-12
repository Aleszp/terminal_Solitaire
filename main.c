#include "cards.h"

int main(void)
{
	srand (time (NULL));
	bool play=true;
	bool game=true;
	card waste[24];
	card tableau[140];
	card foundation[52];
	unsigned char waste_position;
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
		//opróżnij wasteiki 
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
		//deal
		deal(waste, tableau);
		//ustaw wartości domyślne zmiennych
		game=true;
		waste_position=24;
		score=0;
		rozdania=0;
		
		//w tej pętli graczowi wyświetlane są karty i opcje, gracz wybiera akcje
		do
		{
			//wypisz karty
			wypisz(waste, tableau, foundation, waste_position, score);
			
			//pozwól wybrać graczowi co robić
			decyzja=wybor();
			if(decyzja==0)
			{
				fprintf(stdout,"Komenda nierozpozna.\n");
				continue;
			}
			if(decyzja==3)game=false;	//nowe rozdanie?
			else if(decyzja==4)play=false;		//koniec gry?
			else if(decyzja==2)deal_next(waste, &rozdania, &waste_position, &score); //czy gracz chce rozdać kolejne karty?
			//else przeloz();
		}
		while(game&&play); //czy rozdanie trwa?
	}
	while(play); //czy gracz chce jeszcze grać?
	
	return 0;
}
