#include "menu.h"
#include "client.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

menu_t* menu;

void on_join_acknowledged(int value);

static void init_textbox()
{
    menu->textbox.x = TEXTBOX_X;
    menu->textbox.y = TEXTBOX_Y;
    menu->textbox.width = TEXTBOX_WIDTH;
    menu->textbox.height = TEXTBOX_HEIGHT;
}

static void init_menu()
{
    menu = malloc(sizeof(menu_t));
    memset(menu, 0, sizeof(menu_t));

    menu->connected = 0;

    menu->name.text = malloc(sizeof(char) * NAME_MAX_LEN + 1);
    memset(menu->name.text, 0, sizeof(char) * NAME_MAX_LEN + 1);
    menu->name.len = 0;

    size_t menu_name_length = strlen(TITLE_TEXT);
    menu->title_text = malloc(menu_name_length+1);
    memset(menu->title_text, 0, menu_name_length+1);
    memcpy(menu->title_text, TITLE_TEXT, menu_name_length);

    menu->connect_button = init_button("Connect");
    set_button_rect_properties(menu->connect_button, CONN_BUTTON_X, CONN_BUTTON_Y, CONN_BUTTON_W, CONN_BUTTON_H, WHITE);

    subscribe_to_join_ack(on_join_acknowledged);

    init_textbox();
}


void draw_menu()
{
    BeginDrawing();

    ClearBackground(DARKGRAY);

    Font f = GetFontDefault();

    DrawRectangle(menu->textbox.x, menu->textbox.y, menu->textbox.width, menu->textbox.height, WHITE);
    Vector2 name_pos = {NAME_BASE_POS_X - (MeasureTextEx(f, menu->name.text, NAME_FONT_SIZE, NAME_SPACING).x) * 0.5f, menu->textbox.y + NAME_OFFSET_Y};
    DrawTextEx(f, menu->name.text, name_pos, NAME_FONT_SIZE, NAME_SPACING, MAROON);
    DrawText(menu->title_text, TITLE_POS_X, TITLE_POS_Y, TITLE_FONT_SIZE, RED); 

    draw_button(menu->connect_button, CONN_BUTTON_TEXT_X, CONN_BUTTON_TEXT_Y, CONN_BUTTON_TEXT_S, RED);

    DrawText("Insert Name:", menu->textbox.x, menu->textbox.y - 50, 30, RED);

    if(menu->connected)
    {
        DrawText(CONN_TEXT, CONN_TEXT_POS_X, CONN_TEXT_POS_Y, CONN_TEXT_SIZE, GREEN);
    }
    else
    {
        DrawText(NON_CONN_TEXT, NON_CONN_TEXT_POS_X, CONN_TEXT_POS_Y, CONN_TEXT_SIZE, RED);
    }

    EndDrawing();
}

void update_menu()
{
    //update_client();
}

void manage_input_menu()
{
    int key = GetCharPressed();

    name_t* n = &menu->name;

    if((key >= 32) && (key <= 125) && (menu->name.len < NAME_MAX_LEN))
    {
        n->text[menu->name.len] = (char)key;
        n->text[menu->name.len + 1] = '\0';
        n->len++;
    }

    if(IsKeyPressed(KEY_BACKSPACE))
    {
        n->len--;
        if(n->len < 0)
        {
            n->len = 0;
        }
        n->text[n->len] = '\0';
    }

    if(is_button_pressed(menu->connect_button))
    {
        printf("pressed\n");
        if(menu->name.len > 0)
        {
            set_client_name(menu->name.text);
            connect_to_server();
        }
    }
}

void destroy_menu()
{
    free(menu->name.text);
    destroy_button(&menu->connect_button);
    free(menu);
}

void on_join_acknowledged(int value)
{
    menu->connected = value;
}