#include "player.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

player_t* init_player(char* player_name)
{
    player_t* player = malloc(sizeof(player_t));
    if(player == NULL)
    {
        printf("could not initialize player %s\n", player_name);
        return NULL;
    }
    size_t name_len = strlen(player_name);
    player->name = malloc(name_len);
    memcpy(player->name, player_name, name_len);

    return player;
}

// expected pointer to player
void free_player_used_resources(void** player)
{
    player_t* p = (player_t*)*player;
    free(p->name);
}

void destroy_player(player_t** player)
{
    player_t* p = *player;
    free(p->name);
    free(p);
}