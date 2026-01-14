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

/**
 * Flips a coin
 * 
 * Returns either 0 or 1 randomly. Used for the Mysterious Chest trap where user
 * get coins or take damage.
 * 
 * @return 0 or 1
 */
int flip_coin() {
    return rand() % 2;
}

/**
 * Generates a random number between 1 and 500
 * 
 * Used for the Dragon's Padovan sequence challenge. The dragon asks if a number
 * is in the Padovan sequence and user has to answer correctly to avoid damage.
 * 
 * @return Random integer from 1 to 500
 */
int random_500_generator() {
    return (rand() % 500) + 1;
}

FinalFightMoves shield_magic_sword(){
    return (rand() % 3);
}

/**
 * Calculates a number in the Padovan sequence
 * Recursive function that computes the nth Padovan number.
 * 
 * @param n Which position in the sequence to calculate
 * @return The Padovan number at position n
 */
int padovan_sequence(int n){
    if (n==0 || n==1 || n==2){
        return 1;
    }
    return padovan_sequence(n-2) + padovan_sequence(n-3);
}

/**
 * Checks if a number is in the Padovan sequence
 * 
 * Generates Padovan numbers until it finds a match or passes the target.
 * Used for the Dragon's math quiz during combat.
 * 
 * @param num The number to check
 * @return true if num is a Padovan number, false otherwise
 */
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

/**
 * Converts a move enum to its string name
 * Takes a FinalFightMoves value and returns the display name for it.
 * 
 * @param num The move enum value
 * @return String name, "Shield", "Magic", or "Sword"
 */
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

/**
 * Creates an Enemy struct with data from a specific room
 * 
 * Allocates memory and fills in enemy stats based on room number and mission.
 * Handles special damage codes like -100 (dice roll) and -200 (coin flip).
 * The fatal strike for traps with -100 damage gets set to 5 if user has the
 * sword upgrade, otherwise stays -100.
 * 
 * @param game Pointer to current game state
 * @param room_number Which room (1-6 within the mission)
 * @param mission Which mission (1-3 for the main missions)
 * @return Pointer to newly created Enemy, or NULL if allocation failed
 */
Enemy *initialize_enemy(GameState *game, int room_number, unsigned int mission){
    Enemy *enemy = malloc(sizeof(Enemy));
    if (enemy == NULL){
        printf("ERROR: Failed to allocate memory.");
        return NULL;
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

        char buffer[16];
        if (scanf("%15s", buffer) != 1) {
            clean_input();
            continue;
        }
        clean_input();

        if (buffer[1] != '\0') {
            printf("\n%sInvalid input! Try again!%s\n", CL_RED, CL_CLOSE);
            continue;
        }

        char user_input = buffer[0];

        switch (user_input)
        {
        case '1':
            if (game->coins - 4 >= 0){
                game->coins -= 4;
                printf(
                    "\n\n%ssuccessfully purchased!%s\nYou now have %d Health Potions.\n",
                    CL_GREEN, CL_CLOSE, ++game->potions
                );
                break;
            }
            printf(
                "\n\n%sInsufficient coins!%s\n Your balance: %d coins.\n",
                CL_RED, CL_CLOSE, game->coins
            );
            return;
        case '2':
            if (game->extra_sword != 0){
               printf("\n\n%sYou already have the extra sword damage!%s\n", CL_BLUE, CL_CLOSE); 
               break;
            }
            if (game->coins - 5 >= 0){
                game->coins -= 5;
                game->extra_sword = 1;
                printf("\n\n%ssuccessfully purchased!%s\nYour sword now has +1 damage.\n", CL_GREEN, CL_CLOSE);
                break;
            }
            printf(
                "\n\n%sInsufficient coins!%s\n Your balance: %d coins.\n",
                CL_RED, CL_CLOSE, game->coins
            );
            return;
        case '3':
            if (game->extra_armor != 0){
               printf("\n\n%sYou already have the extra armor!%s\n", CL_BLUE, CL_CLOSE);
               break;
            }
            if (game->coins - 10 >= 0){
                game->coins -= 10;
                game->extra_armor = 1;
                printf("\n\n%ssuccessfully purchased!%s\nYou now receive 1 less damage.\n", CL_GREEN, CL_CLOSE);
                break;
            }
            printf(
                "\n\n%sInsufficient coins!%s\n Your balance: %d coins.\n",
                CL_RED, CL_CLOSE, game->coins
            );
            return;
        case 'b':
            return;
        default:
            break;
        }
    }
}

/**
 * @brief Show which missions are available
 * 
 * Displays missions based on what's been completed. If user has been beaten all three
 * main missions and have the key, only show the Dark Lord fight. Otherwise show
 * the uncompleted missions. Update the mission_linker array to map menu choices
 * to actual mission numbers.
 * 
 * @param game Pointer to game state
 * @param mission_linker Array that maps menu numbers to mission IDs
 */
void display_mission_menu(GameState *game, int *mission_linker){
    printf("\nMission Selection Menu:\n\n");

    for (int i=0; i<3; i++) mission_linker[i] = -1;

    if (game->has_key && game->completed_m[0] && game->completed_m[2]){
        printf(
            "1. Dark Lord's Castle - Final Mission: Defeat the Dark Lord.\n"
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
        
        char buffer[16];
        if (scanf("%15s", buffer) != 1) {
            clean_input();
            continue;
        }
        clean_input();

        if (buffer[1] != '\0' ) {
            printf("\n%sInvalid input! Try again!%s\n", CL_RED, CL_CLOSE);
            continue;
        }

        char user_input = buffer[0];

        if (user_input == 'b'){
            return BACK;
        }
        
        int mission_num = -1;
        if (user_input >= '1' && user_input <= '3'){
            mission_num = mission_linker[user_input-'1'];
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
        default:
            break;
        }
    }
}

/**
 * Shows the menu in mission page
 */
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

/**
 * Handles menu options during missions
 * 
 * Option 0 uses a health potion, option 2 enter shop,
 * option 3 display inventory, and 
 * option 4 check for coins and return to village or disply error.
 * 
 * @param game Pointer to game state
 * @param option The menu choice character
 * @return WON if returning to village, BACK otherwise
 */
MissionState mission_menu_handler(GameState *game, char option){
    switch (option){
        case '0':
            if (game->potions > 0){
                game->potions--;
                int rolled_dice = roll_dice();
                game->life = (rolled_dice+game->life) > 20 ? 20 : rolled_dice+game->life;
                printf(
                    "\nYou used your health potions and %shealed +%d%s.\n"
                    "Your current life points: %d\n",
                    CL_GREEN, rolled_dice, CL_CLOSE, game->life
                );
            } else {
                printf("\n%sYou don't have any health potions!%s\n", CL_RED, CL_CLOSE);
            }
            break;
        case '2':
            enter_shop(game);
            break;
        case '3':
            display_inventory(game);
            printf("To use your health potions, enter \"0\"");
            break;
        case '4':
            if (game->coins >= 50){
                game->coins -= 50;
                printf("\n%sYou paid 50 coins to return to the village.%s\n\n", CL_YELLOW, CL_CLOSE);
                sleep(1);
                return WON;
            } else {
                printf("\n%sYou need 50 coins to return to the village! You have %d coins.%s\n", CL_RED, game->coins, CL_CLOSE);
            }
            break;
        default:
            printf("\n%sInvalid option!%s\n", CL_RED, CL_CLOSE);
            break;
    }
    return BACK;
}

MissionState mission_rotting_swamp(GameState *game){

    printf(
        "\n%s=== ROTTING SWAMP ===%s\n"
        "Goals: Defeat 3 Orc Generals of the Dark Lord\n",
        CL_BOLD, CL_CLOSE
    );

    int non_generals = 0;
    int defeated_orc_generals = 0;
    int rooms_visited = 0;

    while (rooms_visited < 10) {
        printf(
            "Mission Status: Defeated %d of 3 Orc Generals.\n",
            defeated_orc_generals
        );

        if (defeated_orc_generals == 3) break;

        display_mission_progression();

        char user_input;
        scanf(" %c", &user_input);
        clean_input();

        if (!is_digit(user_input)){
            printf("\n%sInvalid option!%s\n", CL_RED, CL_CLOSE);
            continue;
        }

        if (user_input == '1'){
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
                game->completed_m[0] = 1;
                return WON;
            }
        }
    }

    printf(
        "\n%sYou successfully completed the Rotting Swamp Mission!%s\n"
        "Returning back to main menu...\n",
        CL_GREEN, CL_CLOSE
    );
    game->completed_m[0] = 1;

    return WON;
}

MissionState mission_haunted_mansion(GameState *game){
    
    printf(
        "\n%s=== HAUNTED MANSION ===%s\n"
        "Recover the key to the Dark Lord's Castle, and defeat a Greater Vampire.\n",
        CL_BOLD, CL_CLOSE
    );

    bool has_vampire = false;
    bool has_demon = false;
    int enemy_slots = 10;
    int rooms_visited = 0;
    
    while (rooms_visited < 10) {
        char text[100] = "\n\nMission Status:\n";
        
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
        
        char buffer[16];
        if (scanf("%15s", buffer) != 1) {
            clean_input();
            continue;
        }
        clean_input();

        if (buffer[1] != '\0' || !is_digit(buffer[0]) ) {
            printf("\n%sInvalid input! Try again!%s\n", CL_RED, CL_CLOSE);
            continue;
        }

        char user_input = buffer[0];

        if (user_input == '1'){
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
                game->completed_m[1] = 1;
                game->has_key++;
                printf("%sYou received the key to the Dark Lord's Castle!%s\n", CL_GREEN, CL_CLOSE);
                return WON;
            }
        }
    }
    
    printf(
        "\n%sYou successfully completed the Hanuted Mansion Mission!%s\n"
        "Returning back to main menu...\n",
        CL_GREEN, CL_CLOSE
    );
    game->completed_m[1] = 1;

    return WON;
}

MissionState mission_crystal_cave(GameState *game){
    
    printf(
        "\n%s=== Crystal Cave ===%s\n"
        "Recover the Hero's sword.\n",
        CL_BOLD, CL_CLOSE
    );

    int non_dragons = 0;
    int rooms_visited = 0;

    while (rooms_visited < 10) {
        char text[80] = "\n\nMission Status:\n";

        if (rooms_visited != non_dragons){
            break;
        } else {
            strcat(text, "Not recovered the Hero's sword.\n");
        }

        printf("%s", text);

        display_mission_progression();

        char user_input;
        scanf(" %c", &user_input);
        clean_input();

        if (!is_digit(user_input)){
            printf("\n%sInvalid option!%s\n", CL_RED, CL_CLOSE);
            continue;
        }

        if (user_input == '1'){
            if (game->life > 0){
                MissionState state = explore_crystal_cave_room(game, &non_dragons);
                if (state == LOST) return LOST;
                else if (state == WON){                
                    printf(
                        "\n%sYou successfully completed the Crystal Cave Mission!%s\n"
                        "Returning back to main menu...\n",
                        CL_GREEN, CL_CLOSE
                    );
                    game->completed_m[2] = 1;

                    return WON;
                }
                rooms_visited++;
            }
        } else {
            MissionState mission_menu_state = mission_menu_handler(game, user_input);
            if (mission_menu_state == WON){
                game->completed_m[2] = 1;
                game->extra_sword = 2;
                printf("%sYou received the Hero's sword and gained permanent %s+2 attack damage%s!%s\n", CL_GREEN, CL_GREEN, CL_CLOSE, CL_CLOSE);
                return WON;
            }
        }
    }
}

/**
 * Pick a random room for Rotting Swamp
 * 
 * Randomly select from rooms 1-6 until user has visited 7 non-general rooms.
 * After that, forces room 6 (Orc General) to appear. This ensures user can
 * actually complete the mission.
 * 
 * @param non_generals Pointer to counter tracking non-general rooms visited
 * @return Room number to encounter
 */
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

/**
 * Picks a random room for Haunted Mansion
 * 
 * Select from rooms 7-12 randomly. Tracks whether user has fought the vampire
 * and demon. When user has running out of rooms, forces the remaining bosses to
 * appear so user can complete the mission.
 * 
 * @param enemy_slots Pointer to remaining room slots
 * @param has_vampire Pointer to vampire defeated flag
 * @param has_demon Pointer to demon defeated flag
 * @return Room number to encounter
 */
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

/**
 * Pick a random room for Crystal Cave
 * 
 * Randomly select from rooms 13-18 until user has visited 9 non-dragon rooms.
 * Then forces room 18 (Ancient Dragon) to appear.
 * 
 * @param non_dragons Pointer to counter for non-dragon rooms
 * @return Room number to encounter
 */
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

/**
 * Runs a combat encounter
 * 
 * Handles the fight loop, player rolls dice, adds sword bonus, checks if enemy
 * is dead. If not, enemy damages back. For the Ancient Dragon,
 * adds a Padovan sequence quiz before damage, answer correctly to skip damage.
 * 
 * @param game Pointer to game state
 * @param enemy Pointer to the enemy being fought
 * @return WON if enemy defeated, LOST if player died
 */
MissionState fight_enemy(GameState *game, Enemy *enemy){
    
    printf(
        "\nThe hero encounters an enemy: %s%s%s"
        "\nthe fight begins.\n",
        CL_BOLD, enemy->name, CL_CLOSE
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
                "The %s is defeated. The hero remains with %s%d life points%s, and receives %d coins.\n",
                enemy->name, CL_GREEN, game->life, CL_CLOSE, enemy->coins
            );
            return WON;
        }

        if (enemy->number == 12+6){

            int random_number = random_500_generator();

            printf(
                "BEFORE I DEAL 10 DAMAGE TO YOU, I'LL GIVE YOU A CHANCE TO TELL ME IF THIS NUMBER IS FROM PADOVAN SEQUENCE!\n"
                "The number: %d\n"
                "%s[Yes/No]%s\n",
                random_number, CL_BOLD, CL_CLOSE
            );

            char user_input[4];
            scanf("%3s", user_input);
            clean_input();
            printf("\n");


            if (
                (strcasecmp(user_input, "Yes")==0 || strcasecmp(user_input, "Y")==0)
                && is_padovan(random_number) ){
                printf("CORRECT! I DEAL YOU NO DAMAGE THIS TIME...\n");
                continue;
            } else {
                printf("WRONG!!!\n");
            }
        }
        
        game->life -= (enemy->damage - game->extra_armor);
        printf(
            "The %s deals %s%d damage%s to the hero. ",
            enemy->name, CL_RED, (enemy->damage - game->extra_armor), CL_CLOSE
        );
        
        if (get_state(game) == LOST) return LOST;
        
        printf(
            "The hero remains with %s%d life points%s.\n",
            CL_GREEN, game->life, CL_CLOSE
        );
    }
}

MissionState get_state(GameState *game){
    if (game->life <= 0){
        printf(
            "\n\n%sYou have been defeated!%s\n"
            "Returning back to main menu...\n",
            CL_RED, CL_CLOSE
        );
        return LOST;
    }
    return WON;
}

/**
 * Handles trap room encounters
 * 
 * Processes trap damage and coin changes. Applies damage minus armor bonus,
 * updates coins, and checks if the player survived.
 * 
 * @param game Pointer to game state
 * @param enemy Pointer to the trap data
 * @return WON if survived, LOST if died from trap
 */
MissionState trap_room_handler(GameState *game, Enemy *enemy){
    printf(
        "\nThe hero encounters a trap: %s%s%s\n",
        CL_BOLD, enemy->name, CL_CLOSE
    );
    if (enemy->damage != 0){
        game->life -= (enemy->damage - game->extra_armor);
        printf(
            "You took %d damage! "
            "The hero remains with %s%d life points%s.\n",
            (enemy->damage - game->extra_armor), CL_GREEN, game->life, CL_CLOSE
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
    if (enemy == NULL){
        return LOST;
    }
    
    if (enemy->room_type == TRAP){
        MissionState trap_state = trap_room_handler(game, enemy);
        free(enemy);
        if (trap_state == LOST){
            return LOST;
        }
        
    } else if (enemy->room_type == FIGHT){
        
        MissionState fight_state = fight_enemy(game, enemy);
        if (fight_state == LOST){
            free(enemy);
            return LOST;
        }
        if (enemy->number == 6) (*defeated_orc_generals)++;
        free(enemy);
        
    }
    
    return WON;
}

MissionState explore_haunted_mansion_room(GameState *game,
    int *enemy_slots, bool *has_vampire, bool *has_demon){

    int chosen_room = random_enemy_haunted_mansion(enemy_slots, has_vampire, has_demon);

    Enemy *enemy = initialize_enemy(game, chosen_room, 1);
    if (enemy == NULL){
        return LOST;
    }

    if (enemy->room_type == TRAP){
        MissionState trap_state = trap_room_handler(game, enemy);
        free(enemy);
        if (trap_state == LOST){
            return LOST;
        }

    } else if (enemy->room_type == FIGHT){

        MissionState fight_state = fight_enemy(game, enemy);
        free(enemy);
        if (fight_state == LOST){
            return LOST;
        }
        if (*has_demon && !game->has_key){
            game->has_key++;
            printf("%sYou received the key to the Dark Lord's Castle!%s", CL_GREEN, CL_CLOSE);
        }

    }
    
    return WON;
}

MissionState explore_crystal_cave_room(GameState *game, int *non_dragons){

    int chosen_room = random_enemy_crystal_cave(non_dragons);

    Enemy *enemy = initialize_enemy(game, chosen_room, 1);
    if (enemy == NULL){
        return LOST;
    }

    if (enemy->room_type == EMPTY){

        printf("\nThe hero encounters an Empty Room!\n");
        free(enemy);

    } else if (enemy->room_type == TRAP){
        MissionState trap_state = trap_room_handler(game, enemy);
        free(enemy);
        if (trap_state == LOST){
            return LOST;
        }

    } else if (enemy->room_type == FIGHT){

        MissionState fight_state = fight_enemy(game, enemy);
        if (fight_state == LOST){
            free(enemy);
            return LOST;
        }
        if (enemy->number == 12+6){
            free(enemy);
            game->extra_sword = 2;
            printf("%sYou received the Hero's sword and gained permanent +2 attack damage!%s", CL_GREEN, CL_CLOSE);
            return WON;
        }
        free(enemy);

    }
    return BACK;
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

        char user_input;
        scanf(" %c", &user_input);
        clean_input();

        if (user_input != '1' && user_input != '2' && user_input != '3'){
            printf("\n%sInvalid option!%s\n", CL_RED, CL_CLOSE);
            continue;
        }

        FinalFightMoves random_chosen = shield_magic_sword();
        char lords_move_name[10];
        strcpy(lords_move_name, name_of_move(random_chosen));

        printf(
            "The Dark Lord has meanwhile chosen the %s .\n",
            lords_move_name
        );

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
                "%sThe hero loses the Round.%s\n",
                lords_move_name, CL_RED, CL_CLOSE
            );

        } else {

            printf(
                "The hero defends himself from the %s of the Dark Lord. "
                "%sThe hero wins the Round.%s\n",
                lords_move_name, CL_GREEN, CL_CLOSE
            );
            won_rounds++;

        }

        if (current_round-won_rounds>2){
            game->life = 0;
            return get_state(game);
        } else if (won_rounds == 3){
            printf(
                "\n%sVICTORY!!!%s\ncongratulations! You %sWON%s the game!\n"
                "Returning back to main menu...\n",
                CL_GREEN, CL_CLOSE, CL_GREEN, CL_CLOSE
            );
            return WON;
        }

        current_round++;
    }
}