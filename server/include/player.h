#ifndef PLAYER_H
#define PLAYER_H

typedef struct player
{
    char* name;
    int room_id;
} player_t;

player_t* init_player(char* name);
int destroy_player(player_t** player);


#endif