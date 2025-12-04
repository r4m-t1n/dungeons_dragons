#include <stdio.h>

typedef struct GameState{
    int time;
    int life;
    int coins;
    int items;
    int completed_m;
    struct GameState *last_saved;
} GameState;

typedef struct SaveNode {
    GameState state;
    struct SaveNode *next;
} SaveNode;