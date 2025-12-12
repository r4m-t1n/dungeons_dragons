#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "games.h"

extern SaveNode *saved_games;

void load_game(void){
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
                current->state.items, count_missions
            );
            current = current->next;
            c++;

        }
        printf("Select a game [1 - %d]:", c);
    }
    
    //int load_game_info[4] = {a.life, a.coin, a.items, a.completed_m};
    // start_game(*load_game_info);
}