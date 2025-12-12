#include "games.h"

extern SaveNode *saved_games;

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