#include <stdlib.h>
#include <stdio.h>

void start_game(int info[4]){
    printf("Village Menu :\n1. Start a mission\n2. Rest\n3. Inventory\n4. Save the game\n5. Exit\nChoose an action [1 -5]:");
    int input;
    scanf("%d", &input);
    switch (input)
    {
    case 1:
        // start_mission();
        break;

    case 2:
        // rest();
        break;

    case 3:
        // inventory();
        break;

    case 4:
        // save_game();
        break;

    case 5:
        // exit_game();
        break;
    
    default:
        break;
    }
}