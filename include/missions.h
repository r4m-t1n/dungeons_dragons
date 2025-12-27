#ifndef MISSIONS_H
#define MISSIONS_H

#include <stdbool.h>
#include "games.h"

typedef struct GameState GameState;

typedef enum {
    WILD_DOG = 1,
    GOBLIN,
    SKELETON,
    ORC,
    POISONOUS_BOG,
    ORC_GENERAL
} RoomType;

typedef struct {
    RoomType type;
    bool cleared;
} DungeonRoom;

typedef struct {
    DungeonRoom rooms[10];
    int room_count;
    int current_room;
    int defeated_orc_generals;
    bool is_completed;
} MissionRSwamp;

typedef struct {
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
void explore_rotting_swamp_room(GameState *game);
void play_rotting_swamp_room(GameState *game, DungeonRoom *room);
int roll_dice();

#endif