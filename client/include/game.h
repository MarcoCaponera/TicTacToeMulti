#ifndef GAME_H
#define GAME_H

#include "client.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TITLE "TicTacToe"

typedef enum game_state
{
    MENU,
    GAME
} game_state_t;

extern game_state_t game_state;
extern int playing;

int game_init();
void game_play();

#endif