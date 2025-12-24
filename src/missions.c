#include <stdio.h>
#include "games.h"
#include "missions.h"

int select_mission(GameState *game){
    while (1) {
        if (!game.has_key) {
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
        switch (user_input)
        {
        case 1:
            // explore_dungeon_room(game);
            break;
        case 2:
            // enter_shop(game);
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