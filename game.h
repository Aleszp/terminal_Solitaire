#ifndef _GAME_H_
#define _GAME_H_

//Procedures and functions used while user plays. There are: UI, and actions por user.
unsigned char decide();

wchar_t *describe(card *const karta, bool wybrana);
unsigned char card_value(card *const karta);
unsigned char card_color(card *const karta);
wchar_t card_sign(unsigned char color);

void show_cards(card_list *const waste, card_list *waste_end, card *const tableau, card *const foundation, unsigned wynik, bool three);
void deal_next(card_list **waste, card_list **waste_end, card_list *const waste_begin, unsigned *const rozdania, int *const score, bool three);
void settings(bool *three, bool *game);
card *remove_from_waste(card_list *waste);
void refresh_waste_pointer(card_list **waste, card_list **waste_end, bool three);

unsigned char choose_tableau();
bool may_add_to_tableau(card *const karta, card *const tableau, unsigned char tableau_id);
void add_to_tableau(card *const karta, card *const tableau, unsigned char tableau_id);

bool may_add_to_foundation(card *const karta, card *const foundation);
void add_to_foundation(card *const karta, card *const foundation);
unsigned char where_from();

card remove_many_from_tableau(card *const tableau, unsigned char tableau_id, bool remove);
bool may_remove_many_from_tableau(card *const tableau, unsigned char tableau_id, unsigned char card_id);
void move_many_in_tableau(card *const tableau, unsigned char tableau1_id, unsigned char tableau2_id, unsigned char card_id);
#endif