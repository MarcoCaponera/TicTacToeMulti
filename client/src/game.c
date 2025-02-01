#include "game.h"
#include "tictactoe_server.h"
#include <stdio.h>

int playing;
game_state_t game_state;

void game_play()
{
    while (playing)
    {
        switch (game_state)
        {
            case (MENU):
                break;
            case (SELECTION):
                break;
            case (GAME):
                break;
        }
    }
}

void game_init()
{
    if(init_server())
    {
        printf("could not initialize server\n");
    }
}