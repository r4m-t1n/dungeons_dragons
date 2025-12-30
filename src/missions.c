#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "games.h"
#include "constants.h"
#include "missions.h"
#include "game_menu.h"
#include "game_utils.h"

const RoomDetails mission_rooms = {
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

Enemy *initialize_enemy(GameState *game, int room_number, unsigned int mission){
    Enemy *enemy = malloc(sizeof(Enemy));
    if (enemy == NULL){
        printf("ERROR: Failed to allocate memory.");
    }

    int index = ( ( (mission-1) * 6) + room_number) - 1;

    enemy->number = room_number;
    strcpy(enemy->name, mission_rooms.name[index]);
    enemy->room_type = mission_rooms.type[index];

    if (mission_rooms.fatal[index] == -100){
        enemy->fatal_strike = game->extra_sword != 0 ? 5 : mission_rooms.fatal[index];
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
                enemy->damage = 0;
            } else {
                enemy->damage = mission_rooms.damage[index];
                enemy->coins = 0;
                game->life -= mission_rooms.damage[index];
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
                game->extra_sword = 1;
                printf("\n\nSuccessfuly purchased!\nYour sword now has +1 damage.\n");
                break;
            }
            printf(
                "\n\nInsufficient coins!\n Your balance: %d coins.\n",
                game->coins
            );
            return;
        case 3:
            if (game->extra_armor != 0){
               printf("\n\nYou already have the extra armor!\n");
               break;
            }
            if (game->coins - 10 >= 0){
                game->coins -= 10;
                game->extra_armor = 1;
                printf("\n\nSuccessfuly purchased!\nYou now receive 1 less damage.\n");
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

MissionState select_mission(GameState *game){
    while (1) {
        if (game->has_key) {
            printf(
                "\nMission Selection Menu :\n\n"
                    "\t1. Rotting Swamp\n"
                    "\t2. Haunted Mansion\n"
                    "\t3. Crystal Cave\n"
                    "\t4. Dark Lord's Castle\n\n"
                "Choose an action [1-4]: "
            );
        } else {
            printf(
                "\nMission Selection Menu :\n\n"
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
            if (mission_rotting_swamp(game) == LOST) return LOST;
            break;
        case 2:
            // mission_haunted_mansion(game);
            break;
        case 3:
            // mission_crystal_cave(game);
            break;
        case -1:
            return BACK;
        default:
            break;
        }
    }
}

MissionState mission_rotting_swamp(GameState *game){

    printf(
        "\n\033[1m=== ROTTING SWAMP ===\033[0m\n"
        "Goals: Defeat 3 Orc Generals of the Dark Lord\n"
    );

    int non_generals = 0;
    int defeated_orc_generals = 0;
    int rooms_visited = 0;

    while (rooms_visited < 10) {
        printf("\n\nMission Status: Defeated %d of 3 Orc Generals.\n");

        if (defeated_orc_generals == 3) break;

        printf(
            "Mission Menu :\n\n"
                "\t1. Explore Dungeon Room\n"
                "\t2. Shop\n"
                "\t3. Inventory\n"
                "\t4. Return to Village (Pay 50 Coins)\n\n"
            "Choose an action [1-4]: ",
            defeated_orc_generals
        );

        int user_input;
        scanf("%d", &user_input);
        clean_input();

        switch (user_input)
        {
        case 0:
            if (game->potions > 0){
                game->potions--;
                int rolled_dice = roll_dice();
                game->life = (rolled_dice+game->life) > 20 ? 20 : rolled_dice+game->life;
                printf(
                    "\nYou used your health potions and \033[32mhealed +%d\033[0m.\n"
                    "Your current life points: %d\n",
                    rolled_dice, game->life
                );
            } else {
                printf("\nYou don't have any health potions!\n");
            }
            break;
        case 1:
            if (game->life > 0){
                MissionState state = explore_rotting_swamp_room(
                    game, &non_generals, &defeated_orc_generals
                );
                if (state == LOST) return LOST;
                rooms_visited++;
            }
            break;
        case 2:
            enter_shop(game);
            break;
        case 3:
            display_inventory(game);
            printf("To use your health potions, enter \"0\"");
            break;
        case 4:
            if (game->coins >= 50){
                game->coins -= 50;
                printf("\n\033[33mYou paid 50 coins to return to the village.\033[0m\n\n");
                sleep(1);
                return WON;
            } else {
                printf("\n\033[31mYou need 50 coins to return to the village! You have %d coins.\033[0m\n", game->coins);
            }
            break;
        default:
            printf("\n\033[31mInvalid option!\033[0m\n");
            break;
        }
    }

    printf(
        "\n\033[32mYou successfully completed the Rotting Swamp Mission!\033[0m\n"
        "Returning back to main menu...\n"
    );
    game->completed_m[0] = 1;

    return WON;
}

int random_enemy_rotting_swamp(int *non_generals){
    int chosen_room;
    int enemy_slots = 10 - (*non_generals);
    if (enemy_slots > 3){
        chosen_room = roll_dice();
        (*non_generals)++;
    } else {
        chosen_room = 6;
    }
    return chosen_room;
}

MissionState fight_enemy(GameState *game, Enemy *enemy){
    while (1){

        int rolled_dice = roll_dice();
        int total_damage = rolled_dice + game->extra_sword;
        printf(
            "A dice is rolled to determine the hero's attack\n"
            "The result: %d\n"
            "Total damage with extra sword: %d\n",
            rolled_dice, total_damage
        );

        if (enemy->fatal_strike <= total_damage){
            printf(
                "The %s is defeated. The hero remains with \033[32m%d life points\033[0m, and receives %d coins.\n",
                enemy->name, game->life, enemy->coins
            );
            return WON;
        }

        game->life -= (enemy->damage - game->extra_armor);
        printf(
            "The %s deals \033[31m%d damage\033[0m to the hero. ",
            enemy->name, (enemy->damage - game->extra_armor)
        );

        if (game->life <= 0){
            game->life = 0;
            return LOST;
        }

        printf(
            "The hero remains with \033[32m%d life points\033[0m.\n",
             game->life
        );
    }
}

MissionState explore_rotting_swamp_room(GameState *game, int *non_generals, int *defeated_orc_generals){
    int chosen_room = random_enemy_rotting_swamp(non_generals);

    Enemy *enemy = initialize_enemy(game, chosen_room, 1);

    if (enemy->room_type == EMPTY){

        printf("\nThe hero encounters an Empty Room!\n");

    } else if (enemy->room_type == TRAP){

        printf(
            "\nThe hero encounters a trap: \033[1m%s\033[0m\n",
            enemy->name
        );
        if (enemy->damage != 0){
            game->life -= (enemy->damage - game->extra_armor);
            printf(
                "You took %d damage! "
                "The hero remains with \033[32m%d life points\033[0m.\n",
                (enemy->damage - game->extra_armor), game->life
            );
        }
        if (enemy->coins > 0){
            printf("You gained %d coins!", enemy->coins);
        } else if (enemy->coins < 0){
            printf("You lost %d coins!", enemy->coins);
        }
        game->coins += enemy->coins;

    } else if (enemy->room_type == FIGHT){

        printf(
            "\nThe hero encounters an enemy: \033[1m%s\033[0m"
            "\nthe fight begins.\n",
            enemy->name
        );

        MissionState fight_state = fight_enemy(game, enemy);
        if (fight_state == LOST){
            printf(
                "\n\n\033[31mThe hero is defeated!\033[0m\n"
                "Returning back to main menu...\n"
            );
            return LOST;
        }
        if (enemy->number == 6) (*defeated_orc_generals)++;

    }

    return WON;
}