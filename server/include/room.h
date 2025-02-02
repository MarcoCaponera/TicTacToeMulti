#ifndef ROOM_H
#define ROOM_H
#include "player.h"

#define PLAYFIELD_SIZE 9

typedef struct room
{
    player_t* owner;
    player_t* challenger;
    player_t* playfield;
    player_t* turn;
    int room_id;
} room_t;

room_t* init_room(player_t* owner, int room_id);
int is_door_open(room_t* room);
int has_started(room_t* room);
int reset(room_t* room);
int destroy_room(room_t** room);

#endif