#ifndef CLIENT_H
#define CLIENT_H

#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif 

typedef struct client
{
    int socket;
    struct sockaddr_in sock_addr;
    char* name;
} client_t;

client_t* init_client();
int set_client_name(client_t* client, const char* name);
void destroy_client(client_t** client);

#endif