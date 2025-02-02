#ifndef TICTACTOESERVER_H
#define TICTACTOESERVER_H

#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include "player.h"
#include "room.h"
#include "dictionary.h"

#define COMMAND_JOIN 0
#define COMMAND_CHALLENGE 1
#define COMMAND_MOVE 2
#define COMMAND_QUIT 3
#define COMMAND_CREATE_ROOM 4

typedef struct server
{
    dictionary_t* players;
    room_t* rooms;
    int room_counter;
    int socket;
    struct sockaddr_in sock_addr;
}server_t;

server_t* init_server();
void start_server(server_t* server);


#endif