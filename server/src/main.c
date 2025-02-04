#include "room.h"
#include "player.h"
#include "server.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    server_t* server = init_server();

    run_server(server);

    return 0;
}