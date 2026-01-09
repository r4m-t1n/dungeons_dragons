/**
 * missions.h
 * Mission system types and functions
 * 
 * Contains all the enums, structs, and function declarations for the mission system.
 * Has stuff for room types, combat moves, enemy data, and the main mission functions.
 */

#ifndef MISSIONS_H
#define MISSIONS_H

#include <stdbool.h>
#include "games.h"

typedef struct GameState GameState;

/**
 * Return values for mission functions
 * Tells user how a mission ended, whether the player died, won, or just backed out.
 */
typedef enum{
    LOST, /**< Player died, game over */
    WON, /**< Mission completed successfully */
    BACK /**< Player returned to village early */
} MissionState;

/**
 * Different kinds of rooms user can encounter
 * 
 * Each room in a mission is one of these types. Determines what happens when user
 * enter, fight an enemy, trigger a trap, or just pass through.
 */
typedef enum{
    FIGHT, /**< Combat encounter, need to defeat an enemy */
    TRAP, /**< Trap room, takes damage or loses coins */
    EMPTY /**< Nothing happens */
} RoomTypes;

/**
 * FinalFightMoves
 * Moves for the Dark Lord boss fight
 * 
 * Rock-paper-scissors style system for the final battle. Shield beats Magic,
 * Magic beats Sword, Sword beats Shield. The values are character codes so user
 * can compare directly with input.
 */
typedef enum{
    SHIELD = '1', /**< Defensive move */
    MAGIC = '2', /**< Magic attack */
    SWORD = '3' /**< Physical attack */
} FinalFightMoves;

/**
 * Data for a single enemy or trap encounter
 * 
 * Created when uset enter a room. Holds all the info about what user is fighting
 * or what trap user hits, name, damage values, rewards, etc.
 */
typedef struct {
    char name[20]; /**< Display name of the enemy or trap */
    unsigned int number; /**< Room number (1-18) */
    int coins; /**< Coins awarded when defeated */
    unsigned short fatal_strike; /**< Damage needed to feat (0 for traps) */
    unsigned short damage; /**< Damage dealt to player per play */
    short room_type; /**< Type of room, FIGHT, TRAP, or EMPTY */
} Enemy;

/**
 * Data table for all mission rooms
 * 
 * Struct that holds the stats for every room across all three missions.
 * Arrays are indexed by room number minus 1. Used by initialize_enemy() to look
 * up room data. This gets filled with all the constants from constants.h.
 */
typedef struct{
    char name[18][20]; /**< Names of rooms */
    unsigned int number[18]; /**< Room numbers */
    RoomTypes type[18]; /**< Type for each room */
    int fatal[18]; /**< Fatal strike values */
    int damage[18]; /**< Damage values */
    int coins[18]; /**< Coin rewards/penalties */
} RoomDetails;

/**
 * Shows mission selection menu and starts chosen mission
 * 
 * Displays available missions based on what user has already completed. 
 * If user beat the Dark Lord, returns WON and the game ends
 * 
 * @param game Pointer to current game state
 * @return LOST if player died, WON if Dark Lord defeated, BACK if returned to village
 */
MissionState select_mission(GameState *game);

/**
 * Mission 1 - Rotting Swamp
 * 
 * Goal is to defeat 3 Orc Generals. Rooms are randomly selected but the last few
 * are guaranteed to be generals if user hasn't fought 3 yet. 10 rooms max.
 * 
 * @param game Pointer to game state
 * @return Mission outcome, LOST, WON, or BACK
 */
MissionState mission_rotting_swamp(GameState *game);

/**
 * Handle one room encounter in Rotting Swamp
 * 
 * Pick a random room, create the enemy, and run the fight or trap. Update
 * the counts for non-generals and defeated generals.
 * 
 * @param game Pointer to game state
 * @param non_generals Pointer to counter for non-general rooms visited
 * @param defeated_orc_generals Pointer to counter for generals defeated
 * @return WON if survived, LOST if died
 */
MissionState explore_rotting_swamp_room(GameState *game, int *non_generals, int *defeated_orc_generals);

/**
 * Mission 2 - Haunted Mansion
 * 
 * Need to defeat both the Greater Vampire and Guardian Demon to get the castle key.
 * Max 10 rooms.
 * 
 * @param game Pointer to game state
 * @return Mission outcome, sets has_key to true on success
 */
MissionState mission_haunted_mansion(GameState *game);

/**
 * Handles one room encounter in Haunted Mansion
 * 
 * Randomly pick a room and manage the enemy encounter flags. Make sure both
 * required enemies appear before running out of rooms.
 * 
 * @param game Pointer to game state
 * @param enemy_slots Pointer to remaining room slots counter
 * @param has_vampire Pointer to flag tracking if vampire is defeated
 * @param has_demon Pointer to flag tracking if demon is defeated
 * @return WON if survived, LOST if died
 */
MissionState explore_haunted_mansion_room(GameState *game, int *enemy_slots, bool *has_vampire, bool *has_demon);

/**
 * Mission 3 - Crystal Cave
 * 
 * Goal is to defeat the Ancient Dragon to get the Hero's sword.
 * Dragon appears when user has cleared enough other rooms. Max 10 rooms.
 * 
 * @param game Pointer to game state
 * @return Mission outcome
 */
MissionState mission_crystal_cave(GameState *game);

/**
 * Handles one room encounter in Crystal Cave
 * 
 * Pick random rooms until the time for the dragon fight. Should handle the empty
 * room type too since this mission has one.
 * 
 * @param game Pointer to game state
 * @param non_dragons Pointer to counter for non-dragon rooms visited
 * @return WON if dragon defeated, LOST if died, BACK otherwise
 */
MissionState explore_crystal_cave_room(GameState *game, int *non_dragons);

/**
 * Mission 4 - Dark Lord's Castle (final mission)
 * 
 * Who wins 3 rounds out of 5 rounds using rock-paper-scissors wins the game.
 * 
 * @param game Pointer to game state
 * @return WON if user beat the Dark Lord, LOST if defeated
 */
MissionState mission_dark_lord(GameState *game);

/**
 * Checks if the player is still alive
 * 
 * If life is 0 or fewer, print game over message and returns LOST.
 * Is called after taking damage to see if user died.
 * 
 * @param game Pointer to game state
 * @return LOST if dead, WON otherwise
 */
MissionState get_state(GameState *game);

/**
 * Opens the shop interface
 * 
 * Lets user buy health potions, sword upgrade, or armor upgrade.
 * Sword and armor can only be bought once.
 * 
 * @param game Pointer to game state, modify coins and inventory
 */
void enter_shop(GameState *game);

/**
 * Rolls a 6-sided dice
 * Generates a random number from 1 to 6.
 * 
 * @return Random number between 1 and 6
 */
int roll_dice();

#endif