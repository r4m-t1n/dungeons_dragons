#include <stdlib.h>
#include <stdio.h>
#include "games.h"
#include "start_game.c"

#define DEFAULT_TIME 0
#define DEFAULT_LIFE_POINT 20
#define DEFAULT_COINS 0
#define DEFAULT_POTIONS 0
#define DEFAULT_EXTRA_SWORD 0
#define DEFAULT_LOWER_ARMOR 0
#define DEFAULT_HAS_KEY 0
#define DEFAULT_COMPLETED_M {0, 0, 0, 0}

extern SaveNode *saved_games;

void create_new_game(){
    GameState *new_game = malloc(sizeof(GameState));
    if (!new_game){
        printf("ERROR: Can't allocate memory.\n");
        return;
    }
    *new_game = (GameState){
        .time = DEFAULT_TIME,
        .life = DEFAULT_LIFE_POINT,
        .coins = DEFAULT_COINS,
        .potions = DEFAULT_POTIONS,
        .extra_sword = DEFAULT_EXTRA_SWORD,
        .lower_armor = DEFAULT_LOWER_ARMOR,
        .has_key = DEFAULT_HAS_KEY,
        .completed_m = DEFAULT_COMPLETED_M
    };

    start_game(new_game);
}