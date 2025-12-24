#ifndef MISSIONS_H
#define MISSIONS_H

#include "games.h"

typedef struct GameState GameState;

typedef struct {
    unsigned short defeated_orc;
    unsigned short opened_room;
} MissionRSwamp;

typedef struct {
    unsigned short completed_num;
    MissionRSwamp mission_rsamp;
} MissionsList;

enum RoomTypes{
    FIGHT,
    TRAP,
    EMPTY
};

typedef struct {
    unsigned int number;
    short room_type;
    unsigned short fatal_strike;
    unsigned short damage;
    int coins;
} Enemy;

enum GameMissions{
    ROTTING_SWAMP = 1,
    HAUNTED_MANSION,
    CRYSTAL_CAVE,
    DARK_LORDS_CASTLE
};

int select_mission(GameState *game);
void mission_rotting_swamp(GameState *game);
void enter_shop(GameState *game);

#endif