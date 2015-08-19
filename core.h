#ifndef _CORE_H_
#define _CORE_H_

//Built-in
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
	bool chosen		:1;
}
card;


typedef struct card_list
{
	card karta;
	struct card_list* prev;
	struct card_list* next;
}card_list;

enum card_number{ACE=1, JACK=11, QUEEN=12, KING=0};
enum card_color{HEARTS=0, CLUBS=1, DIAMONDS=2, SPADES=3};

//Custom
#include "prepare.h"
#include "game.h"

#endif