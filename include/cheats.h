#ifndef CHEATS_H
#define CHEATS_H

#include "games.h"

void cheats_menu();

void modify_life(SaveNode *saved_node);
void modify_coin(SaveNode *saved_node);
void modify_key(SaveNode *saved_node);

int detect_konami(char code, int *char_index);

#endif