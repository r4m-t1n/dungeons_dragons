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
        C_ROOM_1_DAMAGE, C_ROOM_2_DAMAGE, C_ROOM_3_DAMAGE, C_ROOM_4_CODE, C_ROOM_5_DAMAGE, C_ROOM_6_DAMAGE
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

int random_500_generator() {
    return (rand() % 500) + 1;
}

FinalFightMoves shield_magic_sword(){
    return (rand() % 3);
}

int padovan_sequence(int n){
    if (n==0 || n==1 || n==2){
        return 1;
    }
    return padovan_sequence(n-2) + padovan_sequence(n-3);
}

int is_padovan(int num){
    int n = 1;
    while (1){
        int padovan_num = padovan_sequence(n);

        if (padovan_num == num){
            return true;
        } else if (padovan_num > num){
            return false;
        }

        n++;
    }
}

char *name_of_move(FinalFightMoves num){
    switch (num){
        case SHIELD:
            return "Shield";
        
        case MAGIC:
            return "Magic";
        
        case SWORD:
            return "Sword";
        
        default:
            break;
    }
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
                enemy->damage = C_ROOM_4_DAMAGE;
                enemy->coins = 0;
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
                    "\n\n\033[32msuccessfully purchased!\033[0m\nYou now have %d Health Potions.\n",
                    ++game->potions
                );
                break;
            }
            printf(
                "\n\n\033[31mInsufficient coins!\033[0m\n Your balance: %d coins.\n",
                game->coins
            );
            return;
        case 2:
            if (game->extra_sword != 0){
               printf("\n\n\033[34mYou already have the extra sword damage!\033[0m\n"); 
               break;
            }
            if (game->coins - 5 >= 0){
                game->coins -= 5;
                game->extra_sword = 1;
                printf("\n\n\033[32msuccessfully purchased!\033[0m\nYour sword now has +1 damage.\n");
                break;
            }
            printf(
                "\n\n\033[31mInsufficient coins!\033[0m\n Your balance: %d coins.\n",
                game->coins
            );
            return;
        case 3:
            if (game->extra_armor != 0){
               printf("\n\n\033[34mYou already have the extra armor!\033[0m\n");
               break;
            }
            if (game->coins - 10 >= 0){
                game->coins -= 10;
                game->extra_armor = 1;
                printf("\n\n\033[32msuccessfully purchased!\033[0m\nYou now receive 1 less damage.\n");
                break;
            }
            printf(
                "\n\n\033[31mInsufficient coins!\033[0m\n Your balance: %d coins.\n",
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

void display_mission_menu(GameState *game, int *mission_linker){
    printf("\nMission Selection Menu:\n\n");

    for (int i=0; i<3; i++) mission_linker[i] = -1;

    if (game->has_key && game->completed_m[0] && game->completed_m[2]){
        printf(
            "1. Dark Lord's Castle - Final Mission: Defeat the Dark Lord."
            "Choose an action [1-1]: "
        );
        mission_linker[0] = 4;
        return;
    }

    int counter = 0;
    for (int i=0; i<3; i++){
        if (game->completed_m[i] == 0){
            counter++;
            mission_linker[counter-1] = i+1;
            switch (i){

                case 0:
                    printf("\t%d. Rotting Swamp\n", counter);
                    break;

                case 1:
                    printf("\t%d. Haunted Mansion\n", counter);
                    break;

                case 2:
                    printf("\t%d. Crystal Cave\n", counter);
                    break;
            }
        }
    }
    printf("\nChoose an action [1-%d]: ", counter);

}

MissionState select_mission(GameState *game){
    int mission_linker[3];
    
    while (1) {
        display_mission_menu(game, mission_linker);
        
        int user_input;
        scanf("%d", &user_input);
        clean_input();
        
        int mission_num = -1;
        if (user_input >= 1 && user_input <= 3){
            mission_num = mission_linker[user_input-1];
        }

        switch (mission_num)
        {
        case 1:
            if (mission_rotting_swamp(game) == LOST) return LOST;
            break;
        case 2:
            if (mission_haunted_mansion(game) == LOST) return LOST;
            break;
        case 3:
            if (mission_crystal_cave(game) == LOST) return LOST;
            break;
        case 4:
            if (mission_dark_lord(game) == LOST) return LOST;
            else return WON;
        case -1:
            return BACK;
        default:
            break;
        }
    }
}

void display_mission_progression(){
    printf(
        "Mission Menu :\n\n"
            "\t1. Explore Dungeon Room\n"
            "\t2. Shop\n"
            "\t3. Inventory\n"
            "\t4. Return to Village (Pay 50 Coins)\n\n"
        "Choose an action [1-4]: "
    );
}

MissionState mission_menu_handler(GameState *game, int option){
    switch (option){
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

MissionState mission_rotting_swamp(GameState *game){

    printf(
        "\n\033[1m=== ROTTING SWAMP ===\033[0m\n"
        "Goals: Defeat 3 Orc Generals of the Dark Lord\n"
    );

    int non_generals = 0;
    int defeated_orc_generals = 0;
    int rooms_visited = 0;

    while (rooms_visited < 10) {
        printf(
            "\n\nMission Status: Defeated %d of 3 Orc Generals.\n",
            defeated_orc_generals
        );

        if (defeated_orc_generals == 3) break;

        display_mission_progression();

        int user_input;
        scanf("%d", &user_input);
        clean_input();

        if (user_input == 1){
            if (game->life > 0){
                MissionState state = explore_rotting_swamp_room(
                    game, &non_generals, &defeated_orc_generals
                );
                if (state == LOST) return LOST;
                rooms_visited++;
            }
        } else {
            MissionState mission_menu_state = mission_menu_handler(game, user_input);
            if (mission_menu_state == WON){
                return WON;
            }
        }
    }

    printf(
        "\n\033[32mYou successfully completed the Rotting Swamp Mission!\033[0m\n"
        "Returning back to main menu...\n"
    );
    game->completed_m[0] = 1;

    return WON;
}


MissionState mission_haunted_mansion(GameState *game){
    
    printf(
        "\n\033[1m=== HAUNTED MANSION ===\033[0m\n"
        "Recover the key to the Dark Lord's Castle, and defeat a Greater Vampire.\n"
    );

    bool has_vampire = false;
    bool has_demon = false;
    int enemy_slots = 10;
    int rooms_visited = 0;
    
    while (rooms_visited < 10) {
        char text[300] = "\n\nMission Status:\n";
        
        if (has_vampire){
            strcat(text, "Defeated the Greater Vampire\n");
        } else {
            strcat(text, "Not defeated the Greater Vampire\n");
        }
        
        if (has_demon){
            strcat(text, "Defeated the Guardian Demon\n");
        } else {
            strcat(text, "Not defeated the Guardian Demon\n");
        }
        
        printf("%s", text);
        
        if (has_vampire && has_demon) break;
        
        display_mission_progression();
        
        int user_input;
        scanf("%d", &user_input);
        clean_input();
        
        if (user_input == 1){
            if (game->life > 0){
                MissionState state = explore_haunted_mansion_room(
                    game, &enemy_slots, &has_vampire, &has_demon
                );
                if (state == LOST) return LOST;
                rooms_visited++;
            }
        } else {
            MissionState mission_menu_state = mission_menu_handler(game, user_input);
            if (mission_menu_state == WON){
                return WON;
            }
        }
    }
    
    printf(
        "\n\033[32mYou successfully completed the Hanuted Mansion Mission!\033[0m\n"
        "Returning back to main menu...\n"
    );
    game->completed_m[1] = 1;

    return WON;
}


MissionState mission_crystal_cave(GameState *game){
    
    printf(
        "\n\033[1m=== Crystal Cave ===\033[0m\n"
        "Recover the Hero's sword.\n"
    );

    int non_dragons = 0;
    int rooms_visited = 0;

    while (rooms_visited < 10) {
        char text[200] = "\n\nMission Status:\n";

        if (rooms_visited != non_dragons){
            break;
        } else {
            strcat(text, "Not recovered the Hero's sword.\n");
        }

        printf("%s", text);

        display_mission_progression();

        int user_input;
        scanf("%d", &user_input);
        clean_input();

        if (user_input == 1){
            if (game->life > 0){
                MissionState state = explore_crystal_cave_room(game, &non_dragons);
                if (state == LOST) return LOST;
                rooms_visited++;
            }
        } else {
            MissionState mission_menu_state = mission_menu_handler(game, user_input);
            if (mission_menu_state == WON){
                return WON;
            }
        }
    }

    printf(
        "\n\033[32mYou successfully completed the Crystal Cave Mission!\033[0m\n"
        "Returning back to main menu...\n"
    );
    game->completed_m[2] = 1;

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

int random_enemy_haunted_mansion(int *enemy_slots, bool *has_vampire, bool *has_demon){
    int chosen_room = 6+roll_dice();
    if (*enemy_slots == (!*has_vampire) + (!*has_demon)){
        if (!*has_vampire){
            chosen_room = 6+5;
            *has_vampire = true;
        } else if (!*has_demon) {
            chosen_room = 6+6;
            *has_demon = true;
        }
    } else {
        if (chosen_room == 6+5) *has_vampire = true;
        if (chosen_room == 6+6) *has_demon = true;
    }
    (*enemy_slots)--;
    return chosen_room;
}

int random_enemy_crystal_cave(int *non_dragons){
    int chosen_room;
    int enemy_slots = 10 - (*non_dragons);
    if (enemy_slots > 1){
        chosen_room = 12+roll_dice();
        (*non_dragons)++;
    } else {
        chosen_room = 12+6;
    }
    return chosen_room;
}

MissionState fight_enemy(GameState *game, Enemy *enemy){
    
    printf(
        "\nThe hero encounters an enemy: \033[1m%s\033[0m"
        "\nthe fight begins.\n",
        enemy->name
    );
    
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
            game->coins += enemy->coins;
            printf(
                "The %s is defeated. The hero remains with \033[32m%d life points\033[0m, and receives %d coins.\n",
                enemy->name, game->life, enemy->coins
            );
            return WON;
        }

        if (enemy->number == 12+6){

            int random_number = random_500_generator();

            printf(
                "BEFORE I DEAL 10 DAMAGE TO YOU, I'LL GIVE YOU A CHANCE TO TELL ME IF THIS NUMBER IS FROM PADOVAN SEQUENCE!\n"
                "The number: %d\n"
                "\033[1m[Yes/No]\033[0m\n",
                random_number
            );

            char user_input[10];
            scanf("%9s", user_input);
            clean_input();
            printf("\n");


            if (
                (strcmp(user_input, "Yes")==0 || strcmp(user_input, "yes")==0)
                && is_padovan(random_number) ){
                printf("CORRECT! I DEAL YOU NO DAMAGE THIS TIME...\n");
                continue;
            } else {
                printf("WRONG!!!\n");
            }
        }
        
        game->life -= (enemy->damage - game->extra_armor);
        printf(
            "The %s deals \033[31m%d damage\033[0m to the hero. ",
            enemy->name, (enemy->damage - game->extra_armor)
        );
        
        if (get_state(game) == LOST) return LOST;
        
        printf(
            "The hero remains with \033[32m%d life points\033[0m.\n",
            game->life
        );
    }
}

MissionState get_state(GameState *game){
    if (game->life <= 0){
        printf(
            "\n\n\033[31mYou have been defeated!\033[0m\n"
            "Returning back to main menu...\n"
        );
        return LOST;
    }
    return WON;
}

MissionState trap_room_handler(GameState *game, Enemy *enemy){
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
        printf("You lost %d coins!", enemy->coins*-1);
    }
    game->coins += enemy->coins;
    return get_state(game);
}

MissionState explore_rotting_swamp_room(GameState *game, int *non_generals, int *defeated_orc_generals){
    int chosen_room = random_enemy_rotting_swamp(non_generals);
    
    Enemy *enemy = initialize_enemy(game, chosen_room, 1);
    
    if (enemy->room_type == TRAP){
        MissionState trap_state = trap_room_handler(game, enemy);
        if (trap_state == LOST){
            return LOST;
        }
        
    } else if (enemy->room_type == FIGHT){
        
        MissionState fight_state = fight_enemy(game, enemy);
        if (fight_state == LOST){
            return LOST;
        }
        if (enemy->number == 6) (*defeated_orc_generals)++;
        
    }
    
    return WON;
}

MissionState explore_haunted_mansion_room(GameState *game,
    int *enemy_slots, bool *has_vampire, bool *has_demon){

    int chosen_room = random_enemy_haunted_mansion(enemy_slots, has_vampire, has_demon);

    Enemy *enemy = initialize_enemy(game, chosen_room, 1);

    if (enemy->room_type == TRAP){
        MissionState trap_state = trap_room_handler(game, enemy);
        if (trap_state == LOST){
            return LOST;
        }

    } else if (enemy->room_type == FIGHT){

        MissionState fight_state = fight_enemy(game, enemy);
        if (fight_state == LOST){
            return LOST;
        }
        if (*has_demon && !game->has_key){
            game->has_key++;
            printf("\033[32mYou received the key to the Dark Lord's Castle!\033[0m");
        }

    }
    
    return WON;
}

MissionState explore_crystal_cave_room(GameState *game, int *non_dragons){

    int chosen_room = random_enemy_crystal_cave(non_dragons);

    Enemy *enemy = initialize_enemy(game, chosen_room, 1);

    if (enemy->room_type == EMPTY){

         printf("\nThe hero encounters an Empty Room!\n");

    } else if (enemy->room_type == TRAP){
        MissionState trap_state = trap_room_handler(game, enemy);
        if (trap_state == LOST){
            return LOST;
        }

    } else if (enemy->room_type == FIGHT){

        MissionState fight_state = fight_enemy(game, enemy);
        if (fight_state == LOST){
            return LOST;
        }
        if (enemy->number == 12+6){
            game->extra_sword = 2;
            printf("\033[32mYou received the Hero's sword and gained permanent \033[32m+2 attack damage\033[0m!\033[0m");
            return WON;
        }

    }
}

MissionState mission_dark_lord(GameState *game){
    int won_rounds = 0;
    int current_round = 1;
    while (1){
        printf(
            "Final Fight | Round %d of 5 | Hero %d - Dark Lord %d.\n\n"
            "Available moves\n"
                "\t1. Shield\n"
                "\t2. Magic\n"
                "\t3. Sword\n"
            "\nSelect one of the menu options [1-3]: ",
            current_round, won_rounds, current_round - won_rounds
        );

        int user_input;
        scanf("%d", &user_input);
        clean_input();

        
        FinalFightMoves random_chosen = shield_magic_sword();
        char lords_move_name[10];
        strcpy(lords_move_name, name_of_move(random_chosen));

        printf(
            "The Dark Lord has meanwhile chosen the %s .\n",
            lords_move_name
        );

        user_input--;

        if (user_input == random_chosen){

            printf(
                "%s against %s!\nRound draw!\n\n",
                lords_move_name, lords_move_name
            );
            continue;

        } else if (
            (user_input == SHIELD && random_chosen == MAGIC) ||
            (user_input == MAGIC && random_chosen == SWORD) ||
            (user_input == SWORD && random_chosen == SHIELD)){

            printf(
                "The hero couldn't defend himself from the %s of the Dark Lord. "
                "\033[31mThe hero loses the Round.\033[0m\n",
                lords_move_name
            );

        } else {

            printf(
                "The hero defends himself from the %s of the Dark Lord. "
                "\033[32mThe hero wins the Round.\033[0m\n",
                lords_move_name
            );
            won_rounds++;

        }

        if (current_round-won_rounds>2){
            game->life = 0;
            return get_state(game);
        } else if (won_rounds == 3){
            printf(
                "\n\033[32mVICTORY!!!\033[0m\ncongratulations! You \033[32mWON\033[0m the game!\n"
                "Returning back to main menu...\n"
            );
            return WON;
        }

        current_round++;
    }
}