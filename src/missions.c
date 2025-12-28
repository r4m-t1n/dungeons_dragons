#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "games.h"
#include "constants.h"
#include "missions.h"
#include "game_menu.h"
#include "game_utils.h"

RoomDetails mission_rooms = {
    .name = {
        R_ROOM_1_NAME, R_ROOM_2_NAME, R_ROOM_3_NAME, R_ROOM_4_NAME, R_ROOM_5_NAME, R_ROOM_6_NAME,
        H_ROOM_1_NAME, H_ROOM_2_NAME, H_ROOM_3_NAME, H_ROOM_4_NAME, H_ROOM_5_NAME, H_ROOM_6_NAME,
        C_ROOM_1_NAME, C_ROOM_2_NAME, C_ROOM_3_NAME, C_ROOM_4_NAME, C_ROOM_5_NAME, C_ROOM_6_NAME
    },
    .number = {
        1, 2, 3, 4, 5, 6,
        7, 8, 9, 10, 11, 12,
        13, 14, 15, 16, 17, 18
    },
    .type = {
        R_ROOM_1_TYPE, R_ROOM_2_TYPE, R_ROOM_3_TYPE, R_ROOM_4_TYPE, R_ROOM_5_TYPE, R_ROOM_6_TYPE,
        H_ROOM_1_TYPE, H_ROOM_2_TYPE, H_ROOM_3_TYPE, H_ROOM_4_TYPE, H_ROOM_5_TYPE, H_ROOM_6_TYPE,
        C_ROOM_1_TYPE, C_ROOM_2_TYPE, C_ROOM_3_TYPE, C_ROOM_4_TYPE, C_ROOM_5_TYPE, C_ROOM_6_TYPE
    },
    .fatal = {
        R_ROOM_1_FATAL, R_ROOM_2_FATAL, R_ROOM_3_FATAL, R_ROOM_4_FATAL, R_ROOM_5_FATAL, R_ROOM_6_FATAL,
        H_ROOM_1_FATAL, H_ROOM_2_FATAL, H_ROOM_3_FATAL, H_ROOM_4_FATAL, H_ROOM_5_FATAL, H_ROOM_6_FATAL,
        C_ROOM_1_FATAL, C_ROOM_2_FATAL, C_ROOM_3_FATAL, C_ROOM_4_FATAL, C_ROOM_5_FATAL, C_ROOM_6_FATAL
    },
    .damage = {
        R_ROOM_1_DAMAGE, R_ROOM_2_DAMAGE, R_ROOM_3_DAMAGE, R_ROOM_4_DAMAGE, R_ROOM_5_DAMAGE, R_ROOM_6_DAMAGE,
        H_ROOM_1_DAMAGE, H_ROOM_2_DAMAGE, H_ROOM_3_DAMAGE, H_ROOM_4_DAMAGE, H_ROOM_5_DAMAGE, H_ROOM_6_DAMAGE,
        C_ROOM_1_DAMAGE, C_ROOM_2_DAMAGE, C_ROOM_3_DAMAGE, C_ROOM_4_DAMAGE, C_ROOM_5_DAMAGE, C_ROOM_6_DAMAGE
    },
    .coins = {
        R_ROOM_1_COINS, R_ROOM_2_COINS, R_ROOM_3_COINS, R_ROOM_4_COINS, R_ROOM_5_COINS, R_ROOM_6_COINS,
        H_ROOM_1_COINS, H_ROOM_2_COINS, H_ROOM_3_COINS, H_ROOM_4_COINS, H_ROOM_5_COINS, H_ROOM_6_COINS,
        C_ROOM_1_COINS, C_ROOM_2_COINS, C_ROOM_3_COINS, C_ROOM_4_COINS, C_ROOM_5_COINS, C_ROOM_6_COINS
    }
};

int roll_dice() {
    return (rand() % 6) + 1;
}

int flip_coin() {
    return rand() % 2;
}

Enemy *initialize_enemy(GameState **game, int room_number, unsigned int mission){
    Enemy *enemy = malloc(sizeof(Enemy));
    if (enemy == NULL){
        printf("ERROR: Failed to allocate memory.");
    }

    int index = ( ( (mission-1) * 6) + room_number) - 1;

    enemy->number = room_number;
    enemy->room_type = mission_rooms.type[index];

    if (mission_rooms.fatal[index] == -100){
        enemy->fatal_strike = (*game)->extra_sword != 0 ? 5 : mission_rooms.fatal[index];
    } else {
        enemy->fatal_strike = mission_rooms.fatal[index];
    }

    switch (mission_rooms.damage[index]){
        case -100:
            enemy->damage = roll_dice();
            break;
        
        case -200:
            int flipped_coin = flip_coin();
            if (flipped_coin == 1){
                enemy->coins = mission_rooms.coins[index];
            } else {
                enemy->damage = mission_rooms.damage[index];
                (*game)->life -= mission_rooms.damage[index];
                printf("You took %d damage!", mission_rooms.damage[index]);
            }
            return enemy;

        default:
            enemy->damage = mission_rooms.damage[index];
            break;
    }

    enemy->coins = mission_rooms.coins[index];

    return enemy;
}

void enter_shop(GameState *game){
    while (1){
        printf(
            "\n\n"
                "----------------------------------------------------------------------------------------------------\n"
                "| N |      Item      |                       Description                        |  Coins Required  |\n"
                "|--------------------------------------------------------------------------------------------------|\n"
                "| 1 |  Health Potion |  Restore until 6 Life Points (rolling a 6-sided dice)    |         4        |\n"
                "| 2 |      Sword     | +1 to the hero attack (permanent, purchasable only once) |         5        |\n"
                "| 3 |      Armor     | -1 from enemy damage (permanent, purchasable only once)  |         10       |\n"
                "----------------------------------------------------------------------------------------------------\n"
                "\nChoose an item to purchase [1-3]: "
        );
        int user_input;
        scanf("%d", &user_input);
        clean_input();

        switch (user_input)
        {
        case 1:
            if (game->coins - 4 >= 0){
                game->coins -= 4;
                printf(
                    "\n\nSuccessfuly purchased!\nYou now have %d Health Potions.\n",
                    ++game->potions
                );
                break;
            }
            printf(
                "\n\nInsufficient coins!\n Your balance: %d coins\n",
                game->coins
            );
            return;
        case 2:
            if (game->extra_sword != 0){
               printf("\n\nYou already have the extra sword damage!\n"); 
               break;
            }
            if (game->coins - 5 >= 0){
                game->coins -= 5;
                printf("\n\nSuccessfuly purchased!\nYour sword now has +1 damage.\n");
                break;
            }
            printf(
                "\n\nInsufficient coins!\n Your balance: %d coins.\n",
                game->coins
            );
            return;
        case 3:
            if (game->lower_armor != 0){
               printf("\n\nYou already have the 1-armor reducer!\n");
               break;
            }
            if (game->coins - 10 >= 0){
                game->coins -= 10;
                printf("\n\nSuccessfuly purchased!\nEnemies now have -1 armor.\n");
                break;
            }
            printf(
                "\n\nInsufficient coins!\n Your balance: %d coins.\n",
                game->coins
            );
            return;
        case -1:
            return;
        default:
            break;
        }
    }
}

int select_mission(GameState *game){
    while (1) {
        if (game->has_key) {
            printf(
                "Mission Selection Menu :\n\n"
                    "\t1. Rotting Swamp\n"
                    "\t2. Haunted Mansion\n"
                    "\t3. Crystal Cave\n"
                    "\t4. Dark Lord's Castle\n\n"
                "Choose an action [1-4]: "
            );
        } else {
            printf(
                "Mission Selection Menu :\n\n"
                    "\t1. Rotting Swamp\n"
                    "\t2. Haunted Mansion\n"
                    "\t3. Crystal Cave\n\n"
                "Choose an action [1-3]: "
            );
        }
        int user_input;
        scanf("%d", &user_input);
        clean_input();

        switch (user_input)
        {
        case 1:
            mission_rotting_swamp(game);
            break;
        case 2:
            // mission_haunted_mansion(game);
            break;
        case 3:
            // mission_crystal_cave(game);
            break;
        default:
            break;
        }
    }
}

void mission_rotting_swamp(GameState *game){
    MissionRSwamp *mission = &game->missions_list.mission_rsamp;

    printf(
        "\n\033[1m=== ROTTING SWAMP ===\033[0m\n"
        "Goals: Defeat 3 Orc Generals of the Dark Lord\n"
    );

    int non_generals = 0;

    while (1) {
        printf(
            "\nMission Status: Defeated %d of 3 Orc Generals.\n\n"
            "Mission Menu :\n\n"
                "\t1. Explore Dungeon Room\n"
                "\t2. Shop\n"
                "\t3. Inventory\n"
                "\t4. Return to Village (Pay 50 Coins)\n\n"
            "Choose an action [1-4]: ",
            mission->defeated_orc_generals
        );

        int user_input;
        scanf("%d", &user_input);
        clean_input();

        switch (user_input)
        {
        case 1:
            if (game->life > 0){
                explore_rotting_swamp_room(game, &non_generals);
            }
            break;
        case 2:
            enter_shop(game);
            break;
        case 3:
            display_inventory(game);
            break;
        case 4:
            if (game->coins >= 50){
                game->coins -= 50;
                printf("\n\033[33mYou paid 50 coins to return to the village.\033[0m\n\n");
                sleep(1);
                return;
            } else {
                printf("\n\033[31mYou need 50 coins to return to the village! You have %d coins.\033[0m\n", game->coins);
            }
            break;
        default:
            printf("\n\033[31mInvalid option!\033[0m\n");
            break;
        }
    }
}

int random_enemy_rotting_swamp(int *non_generals){
    int chosen_room;
    int enemy_slots = 10 - (*non_generals);
    if (enemy_slots > 3){
        chosen_room = roll_dice();
    } else if (enemy_slots == 3){
        chosen_room = ORC_GENERAL;
    }
    return chosen_room;
}

void explore_rotting_swamp_room(GameState *game, int *non_generals){
    MissionRSwamp *mission = &game->missions_list.mission_rsamp;
    while (1){
        int chosen_room = random_enemy_rotting_swamp(non_generals);

        Enemy *enemy = initialize_enemy(&game, chosen_room, 1);

    }
}

void play_rotting_swamp_room(GameState *game, DungeonRoom *room){
    switch (room->type) 
    {
    case WILD_DOG:
        // fight_enemy(game, 2, 1, 0, "Wild Dog");
        break;

    case GOBLIN:
        // fight_enemy(game, 3, 2, 2, "Goblin");
        break;

    case SKELETON:
        // fight_enemy(game, 4, 2, 4, "Skeleton");
        break;

    case ORC:
        // fight_enemy(game, 3, 4, 6, "Orc");
        break;

    case POISONOUS_BOG: {
        printf("\nYou encounter a \033[35mPoisonous Bog\033[0m!\n");
        int dmg = roll_dice();
        game->life -= dmg;
        printf("\033[31mYou take %d poison damage!\033[0m (Life Points: %d)\n", dmg, game->life);
        sleep(1);
        break;
    }

    case ORC_GENERAL:
        // fight_enemy(game, 6, 3, 12, "Orc General")
        break;
    }

    // room->cleared = true;
}