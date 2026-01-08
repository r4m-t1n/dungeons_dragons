/**
 * @file cheats.h
 * Cheat system for modifying saved games
 * 
 * Contains functions for the cheat menu that gets unlocked with the Konami code.
 * Lets user modify life points, coins, and enable the final mission on any save.
 * Also has the Konami code detection logic.
 */

#ifndef CHEATS_H
#define CHEATS_H

#include "games.h"

/**
 * Main cheat menu interface
 * 
 * Shows all saved games and lets user pick one to modify. Once user select a save,
 * user can change life points, coins, or unlock the final mission. It is only 
 * accessible after entering the Konami code in the main menu
 */
void cheats_menu();

/**
 * Changes the life points of a saved game
 * 
 * Prompts for a new life value between 1-20 and updates the save. Keeps asking
 * until user enter a valid number. Values outside 1-20 get rejected.
 * 
 * @param saved_node Pointer to the save you want to modify
 */
void modify_life(SaveNode *saved_node);

/**
 * Changes the coin amount of a saved game
 * 
 * Lets user set any coin amount (as long as it's not negative).
 * Updates the coins field directly.
 * 
 * @param saved_node Pointer to the save to modify
 */
void modify_coin(SaveNode *saved_node);

/**
 * @brief Unlocks the final mission for a save
 * 
 * Sets the has_key flag to true and marks the first three missions as completed.
 * This basically skips user straight to the Dark Lord fight(Marks 
 * missions 1, 2, and 3 as complete automatically).
 * 
 * @param saved_node Pointer to the save to unlock
 */
void modify_key(SaveNode *saved_node);

/**
 * Detects if the Konami code is being entered
 * 
 * Checks each character against the Konami sequence (wwssadadba + space).
 * User pass in each character from user input and it tracks progress using char_index.
 * When the full sequence is entered correctly, returns 1 to unlock cheats.
 * The sequence resets if user type the wrong character
 * 
 * @param code The current character being typed
 * @param char_index Pointer to track position in the sequence (gets reset on wrong input)
 * @return 1 if the full Konami code was just completed, 0 otherwise
 */
int detect_konami(char code, int *char_index);

#endif