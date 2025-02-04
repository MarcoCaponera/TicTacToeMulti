#ifndef GAME_H
#define GAME_H

#include "client.h"

typedef enum game_state
{
    MENU,
    SELECTION,
    GAME
} game_state_t;

extern game_state_t game_state;
extern int playing;
extern client_t* client;

int game_init();
void game_play();

#endif