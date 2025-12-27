#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "games.h"
#include "missions.h"
#include "game_menu.h"
#include "game_utils.h"

int roll_dice() {
    return (rand() % 6) + 1;
}

Enemy initialize_enemy(room_number){
    Enemy enemy = malloc(Enemy);
    enemy->number = room_number;
    // enemy->room_type = 
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
                // explore_rotting_swamp_room(game, &non_generals);
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
    if (10 - non_generals > 3){
        chosen_room = roll_dice();
        if
    } else if (10 - non_generals == 3){
        chosen_room = ORC_GENERAL;
    }
    return chosen_room;
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

    room->cleared = true;
}