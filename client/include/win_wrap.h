// made to resolve collisions between raylib and windows functions
#ifndef WINWRAP_H
#define WINWRAP_H

#include "client.h"

int init_socket();
int init_socket_client(client_t* client);
void send_data_to(int socket, char* address, unsigned short port, char* data, size_t len);
char* rec_data(int socket, char* address, unsigned short port);

#endif