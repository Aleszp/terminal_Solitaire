#include "tableau.hpp"

void tableau::show()
{
	cout<<"Stosiki:"<<endl;
	for(uint8_t pile_id=0;pile_id<7;pile_id++)
	{
		cout<<pile_id<<".";
		(pile[pile_id])->show_line();
		cout<<endl;
	}
	cout<<endl;
}