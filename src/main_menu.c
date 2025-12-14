#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_KONAMI "wwssadadba "

void print_menu(int cheats_enabled){
    if (cheats_enabled){
        printf(
            "Initial Game Menu :\n\n"
                "\t1. New Game\n"
                "\t2. Load Game\n"
                "\t3. Cheats\n"
            "\nChoose an action [1-3]: "
        );
    } else {
        printf(
            "Initial Game Menu :\n\n"
                "\t1. New Game\n"
                "\t2. Load Game\n"
            "\nChoose an action [1-2]: "
        );
    }
}

void main_menu(void){
    char input;
    int idx = 0;
    short cheats_enabled = 0;

    print_menu(cheats_enabled);

    while (1){
        scanf(" %c", &input);
        switch (input)
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
                cheats_enabled = detect_konami(input, &idx);
                break;
        }
        print_menu(cheats_enabled);
    }
}

int detect_konami(char code, int *idx){

    const char *konami = DEFAULT_KONAMI;

    if (code != konami[*idx]){
        *idx = 0;
        return 0;
    }
    (*idx)++;
    if (*idx == strlen(konami)){
        *idx = 0;
        return 1;
    }
    return 0;
}