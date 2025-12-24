#include <stdio.h>
#include "games.h"
#include "missions.h"
#include "game_menu.h"
#include "game_utils.h"

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
               printf("\n\nYou already have the extra sword damage!\n"); 
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
        if (!game->has_key) {
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
    printf(
        "Goals: Defeat 3 Orc Generals of the Dark Lord\n"
        "Mission Status: Defeated %d up 3 Orc Generals.\n\n",
        game->missions_list.mission_rsamp.defeated_orc
    );

    while (1) {
        printf(
            "Mission Menu :\n\n"
                "\t1. Explore Dungeon Room\n"
                "\t2. Shop\n"
                "\t3. Inventory\n"
                "\t4. Return to Village (Pay 50 Coins)\n\n"
            "Choose an action [1-4]: "
        );
        int user_input;
        scanf("%d", &user_input);
        clean_input();

        switch (user_input)
        {
        case 1:
            // explore_dungeon_room(game);
            break;
        case 2:
            enter_shop(game);
            break;
        case 3:
            display_inventory(game);
            break;
        case 4:
            // return_to_village_by_fine(game);
            break;
        default:
            break;
        }
    }
}