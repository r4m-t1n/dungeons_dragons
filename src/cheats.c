#include <stdio.h>
#include <string.h>
#include "games.h"
#include "constants.h"
#include "cheats.h"
#include "game_utils.h"

void cheats_menu(){
    while (1){
        if (print_saved_games() == 0){
            return;
        }

        char selected_option;
        scanf(" %c", &selected_option);
        clean_input();

        if (selected_option == 'b'){
            return;
        } else if (!is_digit(selected_option)){
            printf("\n%sInvalid input!%s\n", CL_RED, CL_CLOSE);
            continue;
        }

        int selected_game = selected_option - '0';

        SaveNode *saved_node = search_game(selected_game);
        if (saved_node == NULL){
            printf("ERROR: the game number you entered does not exist.\n\n");
            continue;
        }

        {
            char *key_available = "Not available";
            if (saved_node->state.has_key) key_available = "Available";
            printf(
                "What do you want to do with this game?\n\n"
                    "\t1. Modify L . POINTS              | Current = %d\n"
                    "\t2. Modify COINS                   | Current = %d\n"
                    "\t3. Enable/disable Final mission   | Current = %s\n\n"
                "Choose an option [1-3]: "
                    ,
                    saved_node->state.life, saved_node->state.coins,
                    key_available
            );
        }

        scanf(" %c", &selected_option);
        clean_input();

        switch (selected_option)
        {
        case '1':
            modify_life(saved_node);
            break;

        case '2':
            modify_coin(saved_node);
            break;

        case '3':
            modify_key(saved_node);
            break;

        case 'b':
            return;

        default:
            break;
        }
    }
}

void modify_life(SaveNode *saved_node){
    int life_point;

    while (1){

        printf("\nEnter the life-points between 1-20: ");
        if (scanf("%d", &life_point) != 1){
            printf("\n%sInvalid input!%s\n", CL_RED, CL_CLOSE);
            clean_input();
            continue;
        }

        clean_input();

        if (life_point < 1 || life_point > 20){
            printf("%d is not a valid life-point!\n", life_point);
            continue;
        }
        saved_node->state.life = life_point;
        printf("The life-point has been set to %d.\n", saved_node->state.life);
        return;
    }
}

void modify_coin(SaveNode *saved_node){
    int coins;

    while (1){

        printf("\nEnter the amount of coins: ");
        if (scanf("%d", &coins) != 1){
            printf("\n%sInvalid input!%s\n", CL_RED, CL_CLOSE);
            clean_input();
            continue;
        }

        clean_input();

        if (coins < 0){
            printf("%d is not a valid coin!\n", coins);
            continue;
        }
        saved_node->state.coins = coins;
        printf("The amount of coins has been set to %d.\n", saved_node->state.coins);
        return;
    }
}

void modify_key(SaveNode *saved_node){

    saved_node->state.has_key = true;
    saved_node->state.completed_m[0] = 1;
    saved_node->state.completed_m[1] = 1;
    saved_node->state.completed_m[2] = 1;

    char *key_available = "Not available";
    if (saved_node->state.has_key) key_available = "Available";

    printf("\nFinal mission's availablity changed: it is %s now.\n", key_available);
}

int detect_konami(char code, int *char_index){

    const char *konami = DEFAULT_KONAMI;

    if (code != konami[*char_index]){
        *char_index = 0;
        return 0;
    }
    (*char_index)++;
    if (*char_index == strlen(konami)){
        *char_index = 0;
        return 1;
    }
    return 0;
}