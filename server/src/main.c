#include "room.h"
#include "player.h"
#include "tictactoe_server.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    server_t* server = init_server();

    start_server(server);

    return 0;
}