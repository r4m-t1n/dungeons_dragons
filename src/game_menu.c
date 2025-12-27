#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "games.h"
#include "constants.h"
#include "game_menu.h"
#include "missions.h"
#include "game_utils.h"

extern SaveNode *saved_games;


void create_new_game(){
    GameState *new_game = malloc(sizeof(GameState));
    if (!new_game){
        printf("ERROR: Can't allocate memory.\n");
        return;
    }
    *new_game = (GameState){
        .time = DEFAULT_TIME,
        .life = DEFAULT_LIFE_POINT,
        .coins = DEFAULT_COINS,
        .potions = DEFAULT_POTIONS,
        .extra_sword = DEFAULT_EXTRA_SWORD,
        .lower_armor = DEFAULT_LOWER_ARMOR,
        .has_key = DEFAULT_HAS_KEY,
        .completed_m = DEFAULT_COMPLETED_M
    };

    start_game(new_game);
    return;
}

void load_game(void){
    while (1) {
        if (print_saved_games() == 0){
            return;
        }

        int selected_game;
        scanf("%d", &selected_game);

        SaveNode *saved_game = search_game(selected_game);
        if (saved_game == NULL){
            printf("ERROR: the game number you entered does not exist.\n\n");
            continue;
        }

        GameState *current_game = malloc(sizeof(GameState));

        if (!current_game){
            printf("ERROR: Can't allocate memory.\n");
            return;
        }

        *current_game = saved_game->state;

        start_game(current_game);
        return;
    }
}


void display_village_menu(){
    printf(
        "Village Menu :\n\n"
            "\t1. Start a mission\n"
            "\t2. Rest\n"
            "\t3. Inventory\n"
            "\t4. Save the game\n"
            "\t5. Exit\n\n"
        "Choose an action [1-5]: "
    );
}

void start_game(GameState *game){
    while (1) {
        display_village_menu();

        int user_input;
        scanf("%d", &user_input);
        clean_input();

        switch (user_input)
        {
        case 1:
            select_mission(game);
            break;
        case 2:
            quick_rest(game);
            break;
        case 3:
            display_inventory(game);
            break;
        case 4:
            save_game(game);
            break;
        case 5:
            exit_game(game);
            return;
        default:
            break;
        }
    }
}

void quick_rest(GameState *game){
    if( game->life != 20 ){
        char *text = "Let's Rest...   Restoring Life Points...";
        int c = 0;
        printf("\n");
        while (text[c] != '\0'){
            printf("%c", text[c]);
            fflush(stdout);
            usleep(0.2 * 1000 * 1000);
            c++;
        }
        game->life = 20;
        printf("\n\033[32mLife Points Restored to 20!\033[0m\n");
        sleep(1);
    } else{
        printf("\n\033[34mYour life points are full!\033[0m\n\n");
    }
    return;
}

void display_inventory(GameState *game){
    printf(
        "\nYour Stats:"
            "\n\t\033[1mLife Points: %d\033[0m"
            "\n\t\033[1mCoins: %d\033[0m"
            "\n\t\033[1mPotions: %d\033[0m"
            "\n\t\033[1mExtra Sword Damage: %d\033[0m"
            "\n\t\033[1mLower Armor Damage: %d\033[0m\n\n",
        game->life, game->coins, game->potions, game->extra_sword, game->lower_armor
    );
    return;
}

void save_game(GameState *current_game) {
    current_game->time = time(NULL);

    SaveNode *new_node = malloc(sizeof(SaveNode));
    if (new_node == NULL) {
        printf("\033[31mERROR: Can't allocate memory.\033[0m\n");
        return;
    }
    new_node->state = *current_game;
    new_node->state.time = time(NULL);
    new_node->next = NULL;

    SaveNode *last_node = search_game(-1);
    if (last_node == NULL){
        saved_games = new_node;
    }
    else{
        last_node->next = new_node;
    }
    printf("\n\033[32mGame Saved Successfully!\033[0m\n\n");
    return;
}

void exit_game(GameState *game){
    printf("You are exiting the game, remember to \033[1msave\033[0m the game so as not to lose your progress.");
    char input[8];
    while (1){
        printf("\nAre you sure to proceed? \033[1m[Yes/No]\033[0m\n");
        scanf("%7s", input);
        clean_input();
        
        if (strcmp(input, "Yes") == 0){
            free(game);
            return;
        } else if (strcmp(input, "No") == 0){
            start_game(game);
            return;
        } else {
            printf("\n\033[31mInvalid input\033[0m\n.");
            start_game(game);
            return;
        }
    }
}