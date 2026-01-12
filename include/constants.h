/**
 * @file constants.h
 * Game constants and room definitions for all missions
 * 
 * Has all the default starting values and defines every room/enemy in the three
 * main missions. Each room has a name, type, damage values, and coin rewards.
 * Organized them by mission: R for Rotting Swamp, H for Haunted Mansion, and
 * C for Crystal Cave.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "missions.h"

/**
 * GameDefaults Values. Starting values when creating a new game
 */
#define DEFAULT_KONAMI "wwssadadba " /**< The Konami code sequence - wwssadadba followed by space */
#define DEFAULT_TIME 0 /**< Starting timestamp - set to 0 until first save */
#define DEFAULT_LIFE_POINT 20 /**< Starting life points - full health */
#define DEFAULT_COINS 0 /**< Starting coins */
#define DEFAULT_POTIONS 0 /**< Starting potions */
#define DEFAULT_EXTRA_SWORD 0 /**< Starting sword bonus */
#define DEFAULT_EXTRA_ARMOR 0 /**< Starting armor bonus */
#define DEFAULT_HAS_KEY 0 /**< Starting key status: false */
#define DEFAULT_COMPLETED_M {0, 0, 0, 0} /** Starting mission completion: all zeros (none completed) */

/**
 * Rotting Swamp Mission Rooms
 * Enemy and trap definitions for mission 1
 * This mission has 6 rooms total. Goal is to defeat 3 Orc Generals.
 */
#define R_ROOM_1_NAME "Wild Dog" /**< Room 1 enemy name */
#define R_ROOM_1_TYPE FIGHT /**< Room 1 is a fight encounter */
#define R_ROOM_1_FATAL 2 /**< Damage needed to kill */
#define R_ROOM_1_DAMAGE 1 /**< Damage this enemy deals per turn */
#define R_ROOM_1_COINS 0 /**< Coins gained when defeated */

#define R_ROOM_2_NAME "Goblin" /**< Room 2 enemy name */
#define R_ROOM_2_TYPE FIGHT /**< Room 2 is a fight */
#define R_ROOM_2_FATAL 3 /**< Damage needed to kill */
#define R_ROOM_2_DAMAGE 2 /**< Damage this enemy deals per turn */
#define R_ROOM_2_COINS 2 /**< Coins gained when defeated */

#define R_ROOM_3_NAME "Skeleton" /**< Room 3 enemy name */
#define R_ROOM_3_TYPE FIGHT /**< Room 3 is a fight */
#define R_ROOM_3_FATAL 4 /**< Damage needed to kill */
#define R_ROOM_3_DAMAGE 2 /**< Damage this enemy deals per turn */
#define R_ROOM_3_COINS 4 /**< Coins gained when defeated */

#define R_ROOM_4_NAME "Orc" /**< Room 4 enemy name */
#define R_ROOM_4_TYPE FIGHT /**< Room 4 is a fight */
#define R_ROOM_4_FATAL 3 /**< Damage needed to kill */
#define R_ROOM_4_DAMAGE 4 /**< Damage this enemy deals per turn */
#define R_ROOM_4_COINS 6 /**< Coins gained when defeated */

#define R_ROOM_5_NAME "Poisonous Bog" /**< Room 5 enemy name */
#define R_ROOM_5_TYPE TRAP /**< Room 5 is a trap */
#define R_ROOM_5_FATAL 0 /**< Damage needed to kill */
#define R_ROOM_5_DAMAGE -100 /**< Damage this enemy deals per turn */
#define R_ROOM_5_COINS 0 /**< Coins gained when defeated */

#define R_ROOM_6_NAME "Orc General" /**< Room 6 enemy name */
#define R_ROOM_6_TYPE FIGHT /**< Room 6 is a fight */
#define R_ROOM_6_FATAL 6 /**< Damage needed to kill */
#define R_ROOM_6_DAMAGE 3 /**< Damage this enemy deals per turn */
#define R_ROOM_6_COINS 12 /**< Coins gained when defeated */


/**
 * Haunted Mansion Mission Rooms
 * Enemy and trap definitions for mission 2
 * This mission has 6 rooms. Goal is to defeat the Greater Vampire and Guardian
 * Demon to get the key to the Dark Lord's castle.
 */
#define H_ROOM_1_NAME "Dark Hatch"
#define H_ROOM_1_TYPE TRAP
#define H_ROOM_1_FATAL 0
#define H_ROOM_1_DAMAGE 3
#define H_ROOM_1_COINS 0

#define H_ROOM_2_NAME "Bat"
#define H_ROOM_2_TYPE FIGHT
#define H_ROOM_2_FATAL 2
#define H_ROOM_2_DAMAGE 2
#define H_ROOM_2_COINS 1

#define H_ROOM_3_NAME "Zombie"
#define H_ROOM_3_TYPE FIGHT
#define H_ROOM_3_FATAL 3
#define H_ROOM_3_DAMAGE 2
#define H_ROOM_3_COINS 2

#define H_ROOM_4_NAME "Phantom"
#define H_ROOM_4_TYPE FIGHT
#define H_ROOM_4_FATAL 5
#define H_ROOM_4_DAMAGE 2
#define H_ROOM_4_COINS 4

#define H_ROOM_5_NAME "Greater Vampire"
#define H_ROOM_5_TYPE TRAP
#define H_ROOM_5_FATAL 4
#define H_ROOM_5_DAMAGE 4
#define H_ROOM_5_COINS 7

#define H_ROOM_6_NAME "Guardian Demon"
#define H_ROOM_6_TYPE FIGHT
#define H_ROOM_6_FATAL 4
#define H_ROOM_6_DAMAGE 6
#define H_ROOM_6_COINS 10


/**
 * Crystal Cave Mission Rooms
 * Enemy and trap definitions for mission 3
 * This mission has 6 rooms including an empty one. Goal is to reach and defeat
 * the Ancient Dragon to get the Hero's sword.
 */
#define C_ROOM_1_NAME "Empty Room"
#define C_ROOM_1_TYPE EMPTY /**< Room 1 is a empty */
#define C_ROOM_1_FATAL 0
#define C_ROOM_1_DAMAGE 0
#define C_ROOM_1_COINS 0

#define C_ROOM_2_NAME "Falling Crystals"
#define C_ROOM_2_TYPE TRAP
#define C_ROOM_2_FATAL 0
#define C_ROOM_2_DAMAGE 2
#define C_ROOM_2_COINS 0

#define C_ROOM_3_NAME "Unsafe Bridge"
#define C_ROOM_3_TYPE TRAP
#define C_ROOM_3_FATAL 0
#define C_ROOM_3_DAMAGE 0
#define C_ROOM_3_COINS -3

#define C_ROOM_4_NAME "Mysterious Chest"
#define C_ROOM_4_TYPE TRAP
#define C_ROOM_4_FATAL 0
#define C_ROOM_4_CODE -200
#define C_ROOM_4_DAMAGE 2
#define C_ROOM_4_COINS 10

#define C_ROOM_5_NAME "Steep Cliff"
#define C_ROOM_5_TYPE TRAP
#define C_ROOM_5_FATAL 0
#define C_ROOM_5_DAMAGE -100
#define C_ROOM_5_COINS 0

#define C_ROOM_6_NAME "Ancient Dragon"
#define C_ROOM_6_TYPE FIGHT
#define C_ROOM_6_FATAL 5
#define C_ROOM_6_DAMAGE 10
#define C_ROOM_6_COINS 12

#endif
