#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include <stdint.h>

typedef struct button
{
    Rectangle area;
    char* name;
    Color color;
} button_t;

button_t* init_button(const char* name);
int is_button_pressed(button_t* button);
void destroy_button(button_t** button);
void draw_button(button_t* button, size_t name_offset_x, size_t name_offset_y, size_t font_size, Color text_color);
void set_button_rect_properties(button_t* button, size_t x, size_t y, size_t width, size_t height, Color c);
#endif