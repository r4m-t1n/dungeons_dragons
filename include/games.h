/**
 * @file games.h
 * Core game data structures
 * 
 * Defines the main structures for storing game state and saved games. GameState
 * holds everything about the current player status, and SaveNode is for the linked
 * list of saves.
 */

#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <stdbool.h>
#include "missions.h"

/**
 * Stores all the player's current game data
 * 
 * This struct has everything about the player: health, money, inventory, which
 * missions they've beaten, etc. Gets passed around to basically every function
 * since they all need to read or modify the game state somehow.
 */
typedef struct GameState{
    time_t time; /**< When the game was last saved */
    int coins; /**< Current money */
    int life; /**< Current health points (max is 20) */
    unsigned int completed_m[4]; /**< Array tracking which missions are done (0 or 1 for each) */
    unsigned int potions; /**< Number of health potions in inventory */
    unsigned short extra_sword; /**< Sword damage bonus (0, 1, or 2) */
    unsigned short extra_armor; /**< Armor damage reduction (0 or 1) */
    bool has_key; /**< Whether player has the key to Dark Lord's castle */
} GameState;

/**
 * Node for the saved games linked list
 * 
 * Each save is stored as one of these nodes. The list lets user have multiple
 * saves at once. When user load a game, it copies the state from a node into
 * a new GameState.
 */
typedef struct SaveNode{
    GameState state; /**< The actual game data for this save */
    struct SaveNode *next; /**< Pointer to next save in the list (NULL if last) */
} SaveNode;

#endif