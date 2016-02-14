#include "waste.hpp"

card* waste::remove_current()
{
	if(current==NULL)
		return NULL;
	if(current==first)
		first=first->below;
	if(current->below!=NULL)
		(current->below)->above=current->above;
	if(current->above!=NULL)
		(current->above)->below=current->below;
	
	card *tmp=current;
	current=tmp->below;
	tmp->above=NULL;
	tmp->below=NULL;
	
	return current;
}

void waste::next(bool three_)
{
	if(current==NULL)
	{
		current=first;
		update_third_ptr();
		return;
	}
	for(uint8_t i=three_?3:1;i>0;i--)
	{
		if(three_&&third==NULL)
		{
			current=NULL;
			update_third_ptr();
			return;
		}
		if(current->below!=NULL)
			current=current->below;
		else
			current=NULL;
	}
	update_third_ptr();
}

void waste::show(bool three_)
{
	if(!three_)
	{
		cout<<"Talia:"<<current->show_card()<<endl;
	}
	else
	{
		cout<<"Talia:";
		card *tmp=current;
		while(tmp!=third)
		{
			cout<<tmp->show_card();
			tmp=tmp->below;
		}
		cout<<endl;
	}
}

void waste::update_third_ptr()
{
	third=current;
	if(third==NULL)
		return;
	for(uint8_t i=0;i<3;i++)
	{
		if(third->below==NULL)
		{
			third=NULL;
			return;
		}
		else
			third=third->below;
	}
}

void waste::add(card card_)
{
	if(first==NULL)
	{
		first=new card;
		*first=card_;
		current=first;
	}
	else
	{
		(current->below)=new card;
		*(current->below)=card_;
		(current->below)->above=current;
		current=current->below;
	}
}

waste::~waste()
{
	current=first;
	card* ptr;
	do
	{
		ptr=remove_current();
		if(ptr==NULL)
		{
			first=NULL;
			current=NULL;
			return;
		}
		else
		{
			delete ptr;
		}
	}
	while(true);
}
