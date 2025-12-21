#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <stdbool.h>

typedef struct GameState{
    time_t time;
    unsigned int life;
    int coins;
    unsigned int potions;
    unsigned short extra_sword;
    unsigned short lower_armor;
    bool has_key;
    unsigned int completed_m[4];
} GameState;

typedef struct SaveNode {
    GameState state;
    struct SaveNode *next;
} SaveNode;

void main_menu(void);
void start_game(GameState *game);
void load_game(void);
void quick_rest(GameState *game);
void display_inventory(GameState *game);
void save_game(GameState *current_game);
void exit_game(GameState *game);
int total_items(GameState *game);

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