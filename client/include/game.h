#ifndef GAME_H
#define GAME_H

typedef enum game_state
{
    MENU,
    SELECTION,
    GAME
} game_state_t;

extern game_state_t game_state;
extern int playing;

void game_init();
void game_play();

#endif