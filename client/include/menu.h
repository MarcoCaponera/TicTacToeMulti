#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "raylib.h"
#include "general_defines.h"
#include "button.h"
#include <stdint.h>

#define TITLE_TEXT          "TicTacToe"
#define TITLE_POS_X         SCREEN_CENTER_X - 175
#define TITLE_POS_Y         20
#define TITLE_FONT_SIZE     60
#define TITLE_SPACING       1

#define TEXTBOX_X           SCREEN_CENTER_X - TEXTBOX_WIDTH * 0.5f
#define TEXTBOX_Y           180
#define TEXTBOX_WIDTH       500
#define TEXTBOX_HEIGHT      50

#define NAME_BASE_POS_X     SCREEN_CENTER_X
#define NAME_OFFSET_Y       8
#define NAME_FONT_SIZE      40
#define NAME_SPACING        2

#define NAME_MAX_LEN        20

#define CONN_BUTTON_W       175
#define CONN_BUTTON_H       50
#define CONN_BUTTON_X       SCREEN_CENTER_X - CONN_BUTTON_W * 0.5f
#define CONN_BUTTON_Y       250
#define CONN_BUTTON_TEXT_X  27
#define CONN_BUTTON_TEXT_Y  10
#define CONN_BUTTON_TEXT_S  30

#define CONN_TEXT_POS_X     SCREEN_CENTER_X - 110
#define NON_CONN_TEXT_POS_X SCREEN_CENTER_X - 200
#define CONN_TEXT_POS_Y     350
#define CONN_TEXT           "Connected!"
#define CONN_TEXT_LEN       10
#define NON_CONN_TEXT       "Not Connected Yet..."
#define NON_CONN_TEXT_LEN   20
#define CONN_TEXT_SIZE      40

typedef struct name
{
    char* text;
    // not size_t because need sign
    int len;
} name_t;

typedef struct menu
{
    char* title_text;
    button_t* connect_button;
    int connected;
    Rectangle textbox;
    name_t name;
} menu_t;

extern menu_t* menu;

void init_menu();
void draw_menu();
void update_menu();
void manage_input_menu();

void destroy_menu();

#endif