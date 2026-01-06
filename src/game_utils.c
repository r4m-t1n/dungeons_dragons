#include <stdio.h>
#include <stdlib.h>
#include "games.h"
#include "game_utils.h"

extern SaveNode *saved_games;

int print_saved_games(void){
    printf("Saved Games :\n\n");
    SaveNode *current = saved_games;
    if (current == NULL){
        printf("%sUnfortunately, you don't have any saved game.%s\n", CL_RED, CL_CLOSE);
        return 0;
    }
    int c = 0;
    while (current != NULL){
        c++;
        char time[25];
        strftime(time, 25, "%d-%m-%Y %H:%M:%S", localtime(&current->state.time));

        int count_missions = 0;
        for (int i=0; i<4; i++){
            if (current->state.completed_m[i] == 0) break;
            count_missions++;
        }

        printf(
            "%d. %s, %d L. POINTS, %d COINS, %d ITEMS, %d COMPLETED MISSIONS\n",
            c, time, current->state.life, current->state.coins,
            total_items(&current->state), count_missions
        );
        current = current->next;
    }
    printf("\nSelect a game [1-%d]: ", c);
    return 1;
}

SaveNode *search_game(int num){
    if (saved_games == NULL){
        return NULL;
    }
    if (num == -1){
        SaveNode *current = saved_games;
        while (current->next != NULL){
            current = current->next;
        }
        return current;
    }
    if (num > 0){
        int count = 1;
        SaveNode *current = saved_games;
        while (current != NULL){
            if (count == num){
                return current;
            }
            current = current->next;
            count++;
        }
    }
    return NULL;
}

int total_items(GameState *game){
    return game->potions + game->extra_sword + game->extra_armor;
}

void clean_input(){
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int is_digit(char num){
    return (num >= '0' && num <= '9');
}