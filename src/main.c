#include <stdlib.h>
#include <stdio.h>
#include "games.h"
#include "game_menu.h"
#include "cheats.h"

SaveNode *saved_games = NULL;

void print_menu(int cheats_enabled){
    if (cheats_enabled){
        printf(
            "\nInitial Game Menu :\n\n"
                "\t1. New Game\n"
                "\t2. Load Game\n"
                "\t3. Cheats\n"
            "\nChoose an action [1-3]: "
        );
    } else {
        printf(
            "\nInitial Game Menu :\n\n"
                "\t1. New Game\n"
                "\t2. Load Game\n"
            "\nChoose an action [1-2]: "
        );
    }
}

int main(void){
    char input_string[64];
    int char_index = 0;
    short cheats_enabled = 0;

    print_menu(cheats_enabled);

    while (1){
        fgets(input_string, sizeof(input_string), stdin);
        char user_input = input_string[0];

        switch (user_input)
        {
            case '1':
                create_new_game();
                break;
            case '2':
                load_game();
                break;
            case '3':
                if (cheats_enabled){
                    cheats_menu();
                }
                break;
            default:
                if (cheats_enabled){
                    break;
                }
                cheats_enabled = detect_konami(user_input, &char_index);
                break;
        }
        print_menu(cheats_enabled);
    }

    return 0;
}