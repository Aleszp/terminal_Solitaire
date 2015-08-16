#ifndef _CARDS_H_
#define _CARDS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

typedef struct
{
	unsigned char id:6;
	bool visible	:1;
}
card;

typedef struct card_list
{
	card karta;
	struct card_list* prev;
	struct card_list* next;
}card_list;

enum card_number{A=1, J=11, Q=12, K=0};

void deal(card_list* waste_begin, card_list* waste,card *const tableau);
void umiesc(card *const to, card *const from, bool visible);
int losowa(int max);
wchar_t *opisz(card *const karta, bool wybrana);
void wypisz(card_list *const waste, card *const tableau, card *const foundation, unsigned wynik);
unsigned char wybor();
void deal_next(card_list *const waste, unsigned *const rozdania, int *const score);
void add_to_waste(card_list *const waste,card *const from);
card_list* create_waste();
#endif