#include <stdlib.h>
#include "games.h"

extern SaveNode *saved_games;

void print_saved_games(void){
    {
        printf("Saved Games :\n\n");
        SaveNode *current = saved_games;
        if (current == NULL){
            printf("No saved game found.");
            return;
        }
        int c = 1;
        while (current != NULL){
            char time[20];
            strftime(time, 20, "%d-%m-%Y %H:%M:%S", localtime(&current->state.time));

            int count_missions = 0;
            for (int i=0; i<4; i++){
                if (current->state.completed_m[i] == 0) break;
                count_missions++;
            }

            printf(
                "%d. %s, %d L. POINTS, %d COINS, %d ITEMS, %d COMPLETED MISSIONS",
                c, time, current->state.life, current->state.coins,
                total_items(current), count_missions
            );
            current = current->next;
            c++;

        }
        printf("Select a game [1 - %d]:", c);
    }
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
    return game->potions + game->extra_sword + game->lower_armor;
}