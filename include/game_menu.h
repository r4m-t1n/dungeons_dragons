#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <time.h>
#include "games.h"

void create_new_game();
void load_game_menu();
void load_game(SaveNode *saved_game);
void delete_game(SaveNode **head, SaveNode *saved_game);

void start_game(GameState *game);
void quick_rest(GameState *game);
void display_inventory(GameState *game);
void save_game(GameState *current_game);
void exit_game(GameState *game);

#endif