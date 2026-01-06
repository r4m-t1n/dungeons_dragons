/**
 * @file game_utils.h
 * @brief Utility stuff for the game - colors, input handling, save game functions
 * 
 */

#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <time.h>
#include "games.h"

/** Resets color back to normal */
#define CL_CLOSE "\x1B[0m"

/** Red text */
#define CL_RED "\x1B[31m"

/** Green text */
#define CL_GREEN "\x1B[32m"

/** Yellow text */
#define CL_YELLOW "\x1B[33m"

/** Blue text */
#define CL_BLUE "\x1B[34m"

/** Bold text */
#define CL_BOLD "\x1B[1m"

/**
 * @brief Shows all the saved games to the player
 * 
 * This prints a numbered list of saves with info like when it was saved,
 * how much life and coins they have, total items, and completed missions.
 * Returns 0 if there aren't any saves yet.
 * 
 * @return 1 if saves exist, 0 if the save list is empty
 * 
 */
int print_saved_games(void);

/**
 * @brief Finds a saved game by its number
 * 
 * Goes through the save game list and returns the one matching the number.
 * If pass -1, it gives the last save in the list which is useful
 * when adding new saves.
 * 
 * @param num Which save to find (starts at 1), or -1 for the last one
 * @return Pointer to that save, or NULL if it doesn't exist
 */
SaveNode *search_game(int num);

/**
 * @brief Adds up the player's inventory items
 * 
 * Counts potions + extra swords + extra armor to get total items.
 * 
 * @param game The game state to check
 * @return How many items total
 */
int total_items(GameState *game);

/**
 * @brief Clears leftover input from the buffer
 * 
 * scanf leaves junk in the input buffer (especially newlines) so this
 * function just reads and throws away everything until the next line.
 * Should call this after every scanf or weird things happen with input.
 */
void clean_input();

/**
 * @brief Checks if a character is a number
 * 
 * Returns 1 if the character is between '0' and '9', otherwise 0.
 * 
 * @param num Character to check
 * @return 1 if it's a digit, 0 if not
 */
int is_digit(char num);

#endif