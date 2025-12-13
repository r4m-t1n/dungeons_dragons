#include <stdlib.h>
#include <stdio.h>
#include "games.h"

#define DEFAULT_TIME 0
#define DEFAULT_LIFE_POINT 20
#define DEFAULT_COINS 0
#define DEFAULT_ITEMS 0
#define DEFAULT_HAS_KEY 0
#define DEFAULT_COMPLETED_M {0, 0, 0, 0}

extern SaveNode *saved_games;

void create_new_game(){
    GameState new_game = {
        .time = DEFAULT_TIME,
        .life = DEFAULT_LIFE_POINT,
        .coins = DEFAULT_COINS,
        .items = DEFAULT_ITEMS,
        .has_key = DEFAULT_HAS_KEY,
        .completed_m = DEFAULT_COMPLETED_M
    };

    start_game(new_game);
}