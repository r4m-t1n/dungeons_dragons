#ifndef GAME_H
#define GAME_H

#include <time.h>

typedef struct GameState{
    time_t time;
    unsigned int life;
    unsigned int coins;
    unsigned int items;
    unsigned int completed_m;
} GameState;

typedef struct SaveNode {
    GameState state;
    struct SaveNode *next;
} SaveNode;

#endif