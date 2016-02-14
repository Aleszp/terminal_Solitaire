#ifndef _CARD_DECK_HPP_
#define _CARD_DECK_HPP_

#include "card.hpp"
#include "card_deck.hpp"
#include "foundation.hpp"
#include "tableau.hpp"
#include "waste.hpp"


class card_deck
{
	protected:
		foundation found;
		tableau table;
		waste wst;
	
	public:
		void show_cards(bool three_);
		unsigned char get_decision();
		card_deck();
		~card_deck();
		void next_card(bool three){wst.next(three);}
		void reset_waste_current(){wst.reset_current();}
	
};

#endif