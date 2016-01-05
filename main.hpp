#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <stdbool.h>
#include <iostream>
#include <stdint.h>

enum commands{NONE=0,MOVE_CARD=1,NEXT_CARD=2,NEW_GAME=3,END_GAME=4};
enum card_number{ACE=1, JACK=11, QUEEN=12, KING=0};
enum card_symbol{HEARTS=0, CLUBS=1, DIAMONDS=2, SPADES=3};
enum card_color{RED, BLACK};

using namespace std;

void print_version(void);

#endif
