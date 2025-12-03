#include <stdlib.h>
#include <stdio.h>

void main_menu( void ) {
    printf( "Initial Game Menu :\n\n\t1. New Game\n\t2. Load Game\nChoose an action [1 -2]: " );
   
    int input;
    scanf( "%d", &input );
    switch (input) {
        case 1:
            // int firstData[] = { 20, 0, 0, 0 };
            // start_game(*first_data);
            break;
        case 2:
            // int saved_data[4] = READ_USER_DATA;
            // start_game(*saved_data);
            break;
        default:
            break;
    }
}