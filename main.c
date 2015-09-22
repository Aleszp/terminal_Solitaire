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
	unsigned rounds=0;
	unsigned char decision;
	unsigned char tmp8bit=0;
	
	if (!setlocale(LC_CTYPE, "")) 
	{
        fprintf(stderr, "Cannot set locale\n");
        return 1;
    }
	
	//this loop let user play game until he/she quits. In case of winning lets user start new game.
	do
	{
		//clear tableau
		for(card *wsk=tableau;wsk!=tableau+139;wsk++)
		{
			wsk->id=0;
			wsk->visible=true;
			wsk->chosen=false;
		}
		//clear foundation
		for(card *wsk=foundation;wsk!=foundation+52;wsk++)
		{
			wsk->id=0;
			wsk->visible=true;
			wsk->chosen=false;
		}
		//fallback variables values to defualt ones
		score=0;
		rounds=0;
		waste=waste_begin;
		game=true;

		deal(waste_begin, &waste, tableau);
		
		//in this loop UI shows and player makes decisions
		do
		{
			show_cards(waste, tableau, foundation, score, three);
			decision=decide(); //let player decide what to do
			
			switch(decision)
			{
				case 1:
					tmp8bit=choose_tableau();
					if(tmp8bit==0)
						break;
					if(may_add_to_tableau(&(waste->karta), tableau, tmp8bit-1))
					{
						card *tmp=remove_from_waste(waste);
						add_to_tableau(tmp, tableau, tmp8bit-1);
						free(tmp);
					}
				break;
				case 2:
					deal_next(&waste, waste_begin, &rounds, &score,three); //deal next cards?
				break;
				case 3:
					if(may_add_to_foundation(&(waste->karta), foundation))
					{
						card *tmp=remove_from_waste(waste);
						add_to_foundation(tmp, foundation);
						free(tmp);
					}
				break;
				case 4:
					game=false; //new game?
				break;
				case 5:
					settings(&three, &game); //change settings?
				break;
				case 6:
					play=false; //quit program?
				break;
				default:
					fprintf(stdout,"Komenda nierozpozna.\n"); //unknown command
			}
		}
		while(play&&game); //are we still playing?
		if(game&&play)
		{
			char tmp[2]; //three-sign buffer
			fprintf(stdout, "WYGRANA, GRATULACJE! \nRozdać ponownie (T/N)? \nWYBÓR:");
			scanf("%s",tmp);
			if(tmp[0]=='t'||tmp[0]=='T'||tmp[0]=='Y'||tmp[0]=='y')
				play=true;
			else
				play=false;
		}
	}
	while(play); //player wants to play or wants to quit?
	
	return 0;
}
