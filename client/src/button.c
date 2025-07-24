#include "button.h"
#include <stdlib.h>
#include <string.h>

button_t* init_button(const char* name)
{
    button_t* button = malloc(sizeof(button_t));
    if(button == NULL)
    {
        perror("malloc()");
        return NULL;
    }

    size_t name_len = strlen(name);
    button->name = malloc(name_len + 1);
    memset(button->name, 0, name_len + 1);
    memcpy(button->name, name, name_len);
    button->name[name_len] = '\0';

    return button;
}

int is_button_pressed(button_t* button)
{
    Vector2 mouse_pos = GetMousePosition();

    return IsMouseButtonPressed(0) && CheckCollisionPointRec(mouse_pos, button->area);
}

void destroy_button(button_t** button)
{
    button_t* b = *button;
    free(b->name);
    free(b);
}

void draw_button(button_t* button, size_t name_offset_x, size_t name_offset_y, size_t font_size, Color text_color)
{
    DrawRectangle(button->area.x, button->area.y, button->area.width, button->area.height, button->color);

    DrawText(button->name, button->area.x + name_offset_x, button->area.y + name_offset_y, font_size, text_color);
}

void set_button_rect_properties(button_t* button, size_t x, size_t y, size_t width, size_t height, Color c)
{
    button->color = c;
    button->area.height = height;
    button->area.width = width;
    button->area.x = x;
    button->area.y = y;
}