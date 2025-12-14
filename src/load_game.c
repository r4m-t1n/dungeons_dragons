#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "games.h"

extern SaveNode *saved_games;

void load_game(void){
    print_saved_games();

    int selected_game;
    scanf("%d", &selected_game);

    SaveNode *saved_game = search_game(selected_game);

    GameState *current_game = malloc(sizeof(GameState));

    if (!current_game){
        printf("ERROR: Can't allocate memory.\n");
        return;
    }

    *current_game = saved_game->state;

    start_game(current_game);
}