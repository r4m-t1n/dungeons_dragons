#include <stdlib.h>
#include <stdio.h>
#include "games.c"

#define DEFAULT_TIME 0
#define DEFAULT_LIFE_POINT 20
#define DEFAULT_COINS 0
#define DEFAULT_ITEMS 0
#define DEFAULT_COMPLETED_M 0

void new_game(SaveNode **saved_games_list){
    GameState new_game = {
        .time = DEFAULT_TIME,
        .life = DEFAULT_LIFE_POINT,
        .coins = DEFAULT_COINS,
        .items = DEFAULT_ITEMS,
        .completed_m = DEFAULT_COMPLETED_M,
        .last_saved = NULL
    };

    start_game(new_game, &saved_games_list);
}