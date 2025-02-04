#ifndef PLAYER_H
#define PLAYER_H

typedef struct player
{
    char* name;
    int room_id;
} player_t;

player_t* init_player(char* name);
void destroy_player(player_t** player);
// expected pointer to player
// it's for dictionary integration
// the dictionary can clean used resources when removing an element if we pass this function
void free_player_used_resources(void** player);

#endif