#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <stdbool.h>
#include "missions.h"

typedef struct {
    time_t time;
    unsigned int life;
    int coins;
    unsigned int potions;
    unsigned short extra_sword;
    unsigned short lower_armor;
    bool has_key;
    unsigned int completed_m[4];
    MissionsList missions_list;
} GameState;

typedef struct {
    GameState state;
    struct SaveNode *next;
} SaveNode;

#endif