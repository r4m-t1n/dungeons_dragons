#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <stdbool.h>
#include "missions.h"

typedef struct GameState{
    time_t time;
    unsigned int life;
    int coins;
    unsigned int potions;
    unsigned short extra_sword;
    unsigned short lower_armor;
    bool has_key;
    unsigned int completed_m[4];
    struct MissionsList missions_list;
} GameState;

typedef struct SaveNode {
    GameState state;
    struct SaveNode *next;
} SaveNode;

#endif