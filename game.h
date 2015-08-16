#ifndef _GAME_H_
#define _GAME_H_

wchar_t *opisz(card *const karta, bool wybrana);
void wypisz(card_list *const waste, card *const tableau, card *const foundation, unsigned wynik);
unsigned char wybor();
void deal_next(card_list *const waste, unsigned *const rozdania, int *const score);

#endif