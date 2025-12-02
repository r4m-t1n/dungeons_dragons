#include <stdlib.h>
#include <stdio.h>


void main_menu(void){
    printf("Initial Game Menu :\n\n\t1. New Game\n\t2. Load Game\nChoose an action [1 -2]: ");
    char input;
    scanf("%c", &input);
    switch (input)
    {
    case '1':
        // new_game();
        break;
    
    case '2':
        // load_game();
        break;
    
    default:
        break;
    }
}