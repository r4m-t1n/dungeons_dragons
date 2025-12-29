#ifndef MISSIONS_H
#define MISSIONS_H

#include <stdbool.h>
#include "games.h"

typedef struct GameState GameState;

typedef enum{
    FIGHT,
    TRAP,
    EMPTY
} RoomTypes;

typedef struct {
    char name[20];
    unsigned int number;
    int coins;
    unsigned short fatal_strike;
    unsigned short damage;
    short room_type;
} Enemy;

typedef struct{
    char name[18][20];
    unsigned int number[18];
    RoomTypes type[18];
    int fatal[18];
    int damage[18];
    int coins[18];
} RoomDetails;

int select_mission(GameState *game);
void mission_rotting_swamp(GameState *game);
void enter_shop(GameState *game);
void explore_rotting_swamp_room(GameState *game, int *non_generals, int *defeated_orc_generals);
int roll_dice();

#endif