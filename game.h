#ifndef _GAME_H_
#define _GAME_H_

//Procedures and functions used while user plays. There are: UI, and actions por user.

wchar_t *describe(card *const karta, bool wybrana);
unsigned char card_value(card *const karta);
unsigned char card_color(card *const karta);
void show_cards(card_list *const waste, card *const tableau, card *const foundation, unsigned wynik, bool three);
unsigned char decide();
void deal_next(card_list **waste, card_list *const waste_begin, unsigned *const rozdania, int *const score, bool three);
void settings(bool *three, bool *game);
card remove_from_waste(card_list *waste);

#endif