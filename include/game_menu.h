/**
 * @file game_menu.h
 * Main game menu functions and game state management
 * 
 * This header contains all the functions for the main game loop: creating new
 * games, loading/deleting saves, and the village menu where players can start
 * missions, rest, check inventory, etc. Basically everything that happens when
 * you're not in a dungeon.
 */

#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <time.h>
#include "games.h"

/**
 * Creates and starts a new game
 * 
 * Sets up a new GameState with all the default starting values
 * and then launches straight into the game.
 */
void create_new_game();

/**
 * Shows the load game menu
 * 
 * Displays all saved games and lets the player pick one to load or delete.
 * If they choose to load, it calls load_game() and starts playing from that save.
 * 
 * @note Returns to main menu if there are no saved games
 */
void load_game_menu();

/**
 * Loads an existing save and starts playing
 * 
 * Takes a saved game node, copies its state into a new GameState, and starts the
 * game from there. The original save stays in the list unchanged.
 * 
 * @param saved_game Pointer to the save node to load from
 */
void load_game(SaveNode *saved_game);

/**
 * Deletes a saved game from the list
 * 
 * Asks for confirmation then removes the save from the linked list and frees
 * its memory. Handles both the head node and middle nodes properly so the list
 * doesn't break.
 * 
 * @param head Double pointer to the start of the save list (so we can modify it)
 * @param saved_game The specific save to delete
 */
void delete_game(SaveNode **head, SaveNode *saved_game);

/**
 * The main village menu loop
 * 
 * This is where players can start a new mission, rest to restore health,
 * check their inventory, save progress, or exit the game.
 * 
 * @param game Pointer to the current game state
 */
void start_game(GameState *game);

/**
 * Lets the player rest to restore health
 * 
 * Restores life points back to the maximum (20). Has a little animation with
 * the "Let's Rest..." text appearing one character at a time. Does nothing if
 * health is already full.
 * 
 * @param game Pointer to current game state - modifies the life value
 */
void quick_rest(GameState *game);

/**
 * Shows the player's current stats
 * 
 * Prints out life points, coins, potions, and equipment bonuses. Just a simple
 * status display.
 * 
 * @param game Pointer to game state to display
 */
void display_inventory(GameState *game);

/**
 * Saves the current game to the save list
 * 
 * Creates a new save node with the current game state and adds it to the end
 * of the saved games list. Updates the timestamp to the current time so user
 * can see when it was saved.
 * 
 * @param current_game Pointer to the game state to save
 */
void save_game(GameState *current_game);

/**
 * Handles exiting the game
 * 
 * Asks for confirmation before quitting and reminds the player to save. If they
 * confirm, frees the game state memory and returns 1 to show the game should end.
 * 
 * @param game Pointer to current game state - gets freed if player confirms exit
 * @return 1 if player confirms exit, 0 if they cancel
 */
int exit_game(GameState *game);

#endif