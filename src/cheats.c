#include <stdio.h>
#include "games.h"

void cheats_menu(){
    while (1){
        if (print_saved_games() == 0){
            return;
        }

        int selected_game;
        scanf("%d", &selected_game);

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

        int selected_option;
        scanf("%d", &selected_option);

        switch (selected_option)
        {
        case 1:
            modify_life(saved_node);
            break;

        case 2:
            modify_coin(saved_node);
            break;

        case 3:
            modify_key(saved_node);
            break;

        default:
            break;
        }
    }
}

void modify_life(SaveNode *saved_node){
    int life_point;

    printf("\nEnter the life-points between 1-20: ");
    scanf("%d", &life_point);

    if (life_point < 1 || life_point > 20){
        printf("%d is not a valid life-point!\n", life_point);
        return;
    }
    saved_node->state.life = life_point;
    printf("The life-point has been set to %d.\n", saved_node->state.life);
}

void modify_coin(SaveNode *saved_node){
    int coins;

    printf("\nEnter the amount of coins: ");
    scanf("%d", &coins);

    if (coins < 0){
        printf("%d is not a valid coin!\n", coins);
        return;
    }
    saved_node->state.coins = coins;
    printf("The amount of coins has been set to %d.\n", saved_node->state.coins);
}

void modify_key(SaveNode *saved_node){
    
    saved_node->state.has_key = !saved_node->state.has_key;

    char *key_available = "Not available";
    if (saved_node->state.has_key) key_available = "Available";

    printf("\nFinal mission's availablity changed: it is %s now.\n", key_available);
}