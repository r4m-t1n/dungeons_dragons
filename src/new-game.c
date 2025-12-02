#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_LIFE_POINT 20
#define DEFAULT_COINS 0
#define DEFAULT_ITEMS 0
#define DEFAULT_COMPLETED_M 0

void new_game(void){
    int new_game_info[4] = {DEFAULT_LIFE_POINT, DEFAULT_COINS, DEFAULT_ITEMS, DEFAULT_COMPLETED_M};
    start_game(new_game_info);
}