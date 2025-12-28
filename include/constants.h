#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "missions.h"

#define DEFAULT_KONAMI "wwssadadba "

#define DEFAULT_TIME 0
#define DEFAULT_LIFE_POINT 20
#define DEFAULT_COINS 0
#define DEFAULT_POTIONS 0
#define DEFAULT_EXTRA_SWORD 0
#define DEFAULT_LOWER_ARMOR 0
#define DEFAULT_HAS_KEY 0
#define DEFAULT_COMPLETED_M {0, 0, 0, 0}

#define R_ROOM_1_NAME "Wild Dog\0"
#define R_ROOM_1_TYPE FIGHT
#define R_ROOM_1_FATAL 2
#define R_ROOM_1_DAMAGE 1
#define R_ROOM_1_COINS 0


#define R_ROOM_2_NAME "Goblin\0"
#define R_ROOM_2_TYPE FIGHT
#define R_ROOM_2_FATAL 3
#define R_ROOM_2_DAMAGE 2
#define R_ROOM_2_COINS 2


#define R_ROOM_3_NAME "Skeleton\0"
#define R_ROOM_3_TYPE FIGHT
#define R_ROOM_3_FATAL 4
#define R_ROOM_3_DAMAGE 2
#define R_ROOM_3_COINS 4


#define R_ROOM_4_NAME "Orc\0"
#define R_ROOM_4_TYPE FIGHT
#define R_ROOM_4_FATAL 3
#define R_ROOM_4_DAMAGE 4
#define R_ROOM_4_COINS 6


#define R_ROOM_5_NAME "Poisonous Bog\0"
#define R_ROOM_5_TYPE TRAP
#define R_ROOM_5_FATAL 0
#define R_ROOM_5_DAMAGE -100
#define R_ROOM_5_COINS 0

#define R_ROOM_6_NAME "Orc General\0"
#define R_ROOM_6_TYPE FIGHT
#define R_ROOM_6_FATAL 6
#define R_ROOM_6_DAMAGE 3
#define R_ROOM_6_COINS 12

#define H_ROOM_1_NAME "Dark Hatch\0"
#define H_ROOM_1_TYPE TRAP
#define H_ROOM_1_FATAL 0
#define H_ROOM_1_DAMAGE 3
#define H_ROOM_1_COINS 0


#define H_ROOM_2_NAME "Bat\0"
#define H_ROOM_2_TYPE FIGHT
#define H_ROOM_2_FATAL 2
#define H_ROOM_2_DAMAGE 2
#define H_ROOM_2_COINS 1


#define H_ROOM_3_NAME "Zombie\0"
#define H_ROOM_3_TYPE FIGHT
#define H_ROOM_3_FATAL 3
#define H_ROOM_3_DAMAGE 2
#define H_ROOM_3_COINS 2


#define H_ROOM_4_NAME "Phantom\0"
#define H_ROOM_4_TYPE FIGHT
#define H_ROOM_4_FATAL 5
#define H_ROOM_4_DAMAGE 2
#define H_ROOM_4_COINS 4


#define H_ROOM_5_NAME "Greater Vampire\0"
#define H_ROOM_5_TYPE TRAP
#define H_ROOM_5_FATAL 4
#define H_ROOM_5_DAMAGE 4
#define H_ROOM_5_COINS 7

#define H_ROOM_6_NAME "Guardian Demon\0"
#define H_ROOM_6_TYPE FIGHT
#define H_ROOM_6_FATAL 4
#define H_ROOM_6_DAMAGE 6
#define H_ROOM_6_COINS 10


#define C_ROOM_1_NAME "Empty Room\0"
#define C_ROOM_1_TYPE EMPTY
#define C_ROOM_1_FATAL 0
#define C_ROOM_1_DAMAGE 0
#define C_ROOM_1_COINS 0


#define C_ROOM_2_NAME "Falling Crystals\0"
#define C_ROOM_2_TYPE TRAP
#define C_ROOM_2_FATAL 0
#define C_ROOM_2_DAMAGE 2
#define C_ROOM_2_COINS 0


#define C_ROOM_3_NAME "Unsafe Bridge\0"
#define C_ROOM_3_TYPE TRAP
#define C_ROOM_3_FATAL 0
#define C_ROOM_3_DAMAGE 0
#define C_ROOM_3_COINS -3


#define C_ROOM_4_NAME "Mysterious Chest\0"
#define C_ROOM_4_TYPE TRAP
#define C_ROOM_4_FATAL 0
#define C_ROOM_4_DAMAGE 2
#define C_ROOM_4_COINS 10


#define C_ROOM_5_NAME "Steep Cliff\0"
#define C_ROOM_5_TYPE TRAP
#define C_ROOM_5_FATAL 0
#define C_ROOM_5_DAMAGE -100
#define C_ROOM_5_COINS 0

#define C_ROOM_6_NAME "Ancient Dragon\0"
#define C_ROOM_6_TYPE FIGHT
#define C_ROOM_6_FATAL 5
#define C_ROOM_6_DAMAGE 10
#define C_ROOM_6_COINS 12

#endif