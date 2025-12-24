#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <time.h>
#include "games.h"

int print_saved_games(void);
SaveNode *search_game(int num);
int total_items(GameState *game);
void clean_input();

#endif