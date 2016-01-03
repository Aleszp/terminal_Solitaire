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
		void show_cards();
		unsigned char get_decision();
		card_deck();
		~card_deck();
	
};

#endif