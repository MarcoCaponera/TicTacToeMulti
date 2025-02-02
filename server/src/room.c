#include "room.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"

room_t* init_room(player_t* owner, int room_id)
{
    room_t* room = malloc(sizeof(room_t));
    room->room_id = room_id;
    owner->room_id = room_id;
    room->owner = owner;
    room->challenger = NULL;
    room->playfield = malloc(sizeof(player_t*) * PLAYFIELD_SIZE);
    memset(room->playfield, 0, sizeof(player_t*) * PLAYFIELD_SIZE);

    return room;
}

int is_door_open(room_t* room)
{
    return room->challenger != NULL; 
}

int has_started(room_t* room)
{
    for(size_t i = 0; i < PLAYFIELD_SIZE; i++)
    {
        if(&room->playfield[i] != NULL)
        {
            return 0;
        }
    }

    return -1;
}

int reset(room_t* room)
{
    room->challenger = NULL;
    memset(room->playfield, 0, sizeof(player_t*) * PLAYFIELD_SIZE);
    room->turn = room->owner;

    return 0;
}

int destroy_room(room_t** room)
{
    room_t* r = *room;
    free(r->playfield);
    free(r);

    room = NULL;

    return 0;
}