#include <stdio.h>
#include <math.h>
#include <string.h>
#include "server.h"
#include "utils.h"

void tick(server_t* server);
void kick_player(server_t* server, const char* addr_port_couple);

server_t* init_server()
{
    server_t* server = malloc(sizeof(server_t));

    if(server == NULL)
    {
        perror("malloc()");
        return NULL;
    }

    memset(server, 0, sizeof(server_t));

    server->players = dict_init(sizeof(player_t));
    dict_setup(server->players, 10);

#ifdef _WIN32
    WSADATA wsa_data;
    if(WSAStartup(0x0202, &wsa_data))
    {
        printf("unable to initialize winsock2 \n");
        return NULL;
    }
#endif

    server->socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(server->socket < 0)
    {
        printf("unable to initialize the UDP socket \n");
        return NULL;
    }

    // creation of the address
    struct sockaddr_in sin;
    inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr); // creation of a big endian 32 bit address
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9999); // conversion to big endian

    memcpy(&server->sock_addr, &sin, sizeof(struct sockaddr_in));

    if(bind(server->socket, (struct sockaddr*)&sin, sizeof(sin)))
    {
        printf("unable to bind UDP socket\n");
        return NULL;
    }

    printf("server ready\n");

    return server;
}

void run_server(server_t* server)
{
    printf("waiting for packets...\n");

    for(;;)
    {
        tick(server);
    }
}

void tick(server_t* server)
{
    char buffer[MESSAGE_MAX_SIZE];
    struct sockaddr_in sender_in;
    int sender_in_size = sizeof(sender_in);
    int len = recvfrom(server->socket, buffer, MESSAGE_MAX_SIZE, 0, (struct sockaddr*)&sender_in, &sender_in_size);
    if (len < 0)
    {
        return;
    }
    char addr_as_string[64];
    inet_ntop(AF_INET, &sender_in.sin_addr, addr_as_string, 64);
    int rid = ltob(buffer, sizeof(int));
    int command = ltob(&buffer[4], sizeof(int));
    printf("porcoddio %i\n", command);
    if(command == COMMAND_JOIN)
    {
        char* entry = malloc(32);
        size_t addr_len = strlen(addr_as_string);
        memcpy(entry, addr_as_string, addr_len);
        entry[addr_len] = ':';
        char* port = num_to_str(ntohs(sender_in.sin_port), 10);
        memcpy(&entry[addr_len+1], port, strlen(port));
        if(!dict_contains_key(server->players, entry))
        {   
            printf("kicking player\n");
            kick_player(server, entry);
            return;
        }
        printf("adding player %s\n", &buffer[RID_SIZE + COMMAND_SIZE]);
        player_t* new_player = init_player(&buffer[8]);
        dict_add(server->players, entry, new_player); 
    }
    else if(command == COMMAND_CHALLENGE)
    {
        printf("dayumn\n");
    }
}

void kick_player(server_t* server, const char* addr_port_couple)
{
    player_t* bad_player = (player_t*)dict_get_value_by_key(server->players, addr_port_couple);
    if(dict_remove(server->players, addr_port_couple, free_player_used_resources))
    {
        printf("could not remove\n");
    }
}

