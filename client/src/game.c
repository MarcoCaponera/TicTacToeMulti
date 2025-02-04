#include "game.h"
#include "client.h"
#include <stdio.h>

int playing;
game_state_t game_state;
client_t* client;

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

int game_init()
{
    game_state = MENU;
    playing = 1;

    client = init_client();

    return 0;
}