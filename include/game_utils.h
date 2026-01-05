#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <time.h>
#include "games.h"

#define CL_CLOSE	"\x1B[0m"
#define CL_RED		"\x1B[31m"
#define CL_GREEN	"\x1B[32m"
#define CL_YELLOW	"\x1B[33m"
#define CL_BLUE		"\x1B[34m"

int print_saved_games(void);
SaveNode *search_game(int num);
int total_items(GameState *game);
void clean_input();
int is_digit(char num);

#endif