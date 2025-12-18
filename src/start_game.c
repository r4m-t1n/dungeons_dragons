#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "games.h"

extern SaveNode *saved_games;

void start_game(GameState *game){
    printf(
        "Village Menu :\n\n"
            "\t1. Start a mission\n"
            "\t2. Rest\n"
            "\t3. Inventory\n"
            "\t4. Save the game\n"
            "\t5. Exit\n"
        "Choose an action [1 -5]:"
    );
    int input;
    scanf("%d", &input);
    switch (input)
    {
    case 1:
        start_mission(game);
        break;

    case 2:
        rest(game);
        break;

    case 3:
        // inventory();
        break;

    case 4:
        save_game(game);
        break;

    case 5:
        exit_game(game);
        break;

    default:
        break;
    }
}

int start_mission(GameState *game){
    printf(
        "Mission Selection Menu :\n\n"
            "\t1. Rotting Swamp\n"
            "\t2. Haunted Mansion\n"
            "\t3. Crystal Cave\n"
        "Choose an action [1 -3]: "
    );
    int input;
    scanf("%d", &input);
    return input;
}

void rest(GameState *game){
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
    printf("\nLife Points Restored to 20!\n");
    sleep(1);
}

int inventory(GameState *game){
    printf(
        "\nYour Stats:"
            "\n\tLife Points: %d"
            "\n\tCoins: %d"
            "\n\tPotions: %d"
            "\n\tExtra Sword Damage: %d"
            "\n\t Lower Armor Damage: -%d",
        game->life, game->coins, game->potions, game->extra_sword, game->lower_armor
    );
}

void add_save(GameState *current_game) {
    SaveNode *new_node = malloc(sizeof(SaveNode));
    if (new_node == NULL) {
        printf("ERROR: Can't allocate memory.\n");
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
    printf("Game Saved Successfully!\n");
}

void save_game(GameState *current_game){
    current_game->time = time(NULL);
    add_save(current_game);
}

void exit_game(GameState *game){
    printf("You are exiting the game, remember to save the game so as not to lose your progress.");
    char input[8];
    while (1){
        printf("\nAre you sure to proceed? [Yes/No]\n");
        scanf("%7s", input);
        if (strcmp(input, "Yes") == 0){
            free(game);
            main_menu();
            return;
        } else if (strcmp(input, "No") == 0){
            return;
        } else {
            printf("\nInvalid input.");
        }
    }
}