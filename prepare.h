#ifndef _PREPARE_H_
#define _PREPARE_H_

//Procedures and functions ran before user may start. Mainly to create and deal cards.

void deal(card_list* waste_begin, card_list* waste,card *const tableau);
void umiesc(card *const to, card *const from, bool visible);
int losowa(int max);
void add_to_waste(card_list *const waste,card *const from);
card_list* create_waste();

#endif