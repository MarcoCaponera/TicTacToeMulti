#include "game.h"
#include "client.h"
#include "raylib.h"
#include "menu.h"
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TITLE "TicTacToe"

int playing;
game_state_t game_state;

static void init_ray();

int game_init()
{
    init_ray();

    game_state = MENU;
    playing = 1;

    init_client();
    
    init_menu();

    return 0;
}

void game_play()
{
    while (!WindowShouldClose() && playing)
    {
        switch (game_state)
        {
            case (MENU):
                manage_input_menu();
                update_menu();
                draw_menu();
                break;
            case (GAME):
                // gameplay_manage_input();
                // gameplay_update();
                // gameplay_draw();
                break;
        }
        update_client();
    }
}


static void init_ray()
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);

    InitAudioDevice();

    SetTargetFPS(60);
}