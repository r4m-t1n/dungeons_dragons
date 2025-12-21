#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "games.h"

extern SaveNode *saved_games;

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