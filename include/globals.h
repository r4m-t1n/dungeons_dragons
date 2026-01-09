/**
 * @file globals.h
 * Global variable declarations
 * 
 * Just has the extern declaration for the saved games list. The actual variable
 * is defined in main.c but other files need to access it, so this header lets
 * them reference it without getting linker errors.
 */


#ifndef GLOBALS_H
#define GLOBALS_H

#include "games.h"

/**
 *  Head of the saved games linked list
 * 
 * Points to the first save in the list, or NULL if there aren't any saves yet.
 * This is the master list that stores all the player's saved games. Gets modified
 * when user save, load, or delete games.
 */
extern SaveNode *saved_games;

#endif