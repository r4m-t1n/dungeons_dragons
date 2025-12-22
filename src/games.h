#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <stdbool.h>

typedef struct MissionRSwamp{
    unsigned short defeated_orc;
    unsigned short opened_room;
} MissionRSwamp;

typedef struct MissionsList{
    unsigned short completed_num;
    struct MissionRSwamp mission_rsamp;
} MissionsList;

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

void main_menu(void);
int select_mission(GameState *game);
void mission_rotting_swamp(GameState *game);
void start_game(GameState *game);
void load_game(void);
void quick_rest(GameState *game);
void display_inventory(GameState *game);
void save_game(GameState *current_game);
void exit_game(GameState *game);
int total_items(GameState *game);
void modify_life(SaveNode *saved_node);
void modify_coin(SaveNode *saved_node);
void modify_key(SaveNode *saved_node);
int detect_konami(char code, int *char_index);

SaveNode *search_game(int num);
int print_saved_games(void);

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
    ROTTING_SWAMP = 1,
    HAUNTED_MANSION,
    CRYSTAL_CAVE,
    DARK_LORDS_CASTLE
};

#endif