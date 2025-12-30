#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <stdbool.h>
#include "missions.h"

typedef struct GameState{
    time_t time;
    int coins;
    int life;
    unsigned int completed_m[4];
    unsigned int potions;
    unsigned short extra_sword;
    unsigned short extra_armor;
    bool has_key;
} GameState;

typedef struct SaveNode{
    GameState state;
    struct SaveNode *next;
} SaveNode;

#endif