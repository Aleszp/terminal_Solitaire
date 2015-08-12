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

enum card_number{A=1, J=11, Q=12, K=0};

void deal(card *const waste, card *const tableau);
void umiesc(card *const to, card *const from, bool visible);
int losowa(int max);
wchar_t *opisz(card *const karta, bool wybrana);
void wypisz(card *const waste, card *const tableau, card *const foundation,unsigned char waste_position, unsigned wynik);
unsigned char wybor();
void deal_next(card *const waste, unsigned *const rozdania, unsigned char *const waste_position, int *const score);
#endif