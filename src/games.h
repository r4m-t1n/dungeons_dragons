#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <time.h>

typedef struct GameState{
    time_t time;
    unsigned int life;
    int coins;
    unsigned int items;
    unsigned int has_key:1;
    unsigned int completed_m[4];
} GameState;

typedef struct SaveNode {
    GameState state;
    struct SaveNode *next;
} SaveNode;

SaveNode *search_game(int num);

enum RoomTypes{
    FIGHT,
    TRAP,
    EMPTY
};

typedef struct Enemy{
    unsigned int number;
    short room_type;
    unsigned short fatal_strike;
    unsigned short damage;
    int coins;
} Enemy;

enum GameMissions{
    ROTTING_SWAMP,
    HAUNTED_MANSION,
    CRYSTAL_CAVE,
    DARK_LORDS_CASTLE
};

#endif