#ifndef MISSIONS_H
#define MISSIONS_H

#include <stdbool.h>
#include "games.h"

typedef struct GameState GameState;

typedef enum{
    LOST,
    WON,
    BACK
} MissionState;

typedef enum{
    FIGHT,
    TRAP,
    EMPTY
} RoomTypes;

typedef enum{
    SHIELD = '1',
    MAGIC = '2',
    SWORD = '3'
} FinalFightMoves;

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

MissionState select_mission(GameState *game);
MissionState mission_rotting_swamp(GameState *game);
MissionState explore_rotting_swamp_room(GameState *game, int *non_generals, int *defeated_orc_generals);
MissionState mission_haunted_mansion(GameState *game);
MissionState explore_haunted_mansion_room(GameState *game, int *enemy_slots, bool *has_vampire, bool *has_demon);
MissionState mission_crystal_cave(GameState *game);
MissionState explore_crystal_cave_room(GameState *game, int *non_dragons);
MissionState mission_dark_lord(GameState *game);
MissionState get_state(GameState *game);
void enter_shop(GameState *game);
int roll_dice();

#endif