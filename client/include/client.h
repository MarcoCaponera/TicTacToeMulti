#ifndef CLIENT_H
#define CLIENT_H

#include "dynarray.h"
#include "general_net_defines.h"

#define BASE_JA_SUBS                  5
#define JA_CALLBACK_TYPE(callback)    void(*callback)(int)

typedef struct client
{
    int socket;
    unsigned short addr_family;
    unsigned short port;
    char* name;
} client_t;

extern client_t* client;
extern dynarray_t* join_acknowledge_event;

client_t* init_client();
int set_client_name(const char* name);
void destroy_client();
int connect_to_server();
void update_client();
void subscribe_to_join_ack(JA_CALLBACK_TYPE(callback));
void unsubscribe_from_join_ack(JA_CALLBACK_TYPE(callback));

#endif