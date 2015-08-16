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
}
card;

typedef struct card_list
{
	card karta;
	struct card_list* prev;
	struct card_list* next;
}card_list;

enum card_number{A=1, J=11, Q=12, K=0};

//Custom
#include "prepare.h"
#include "game.h"

#endif