#include <stdio.h>
#include "client.h"
#include "win_wrap.h"
#include "utils.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

client_t* client;
dynarray_t* join_acknowledge_event;

client_t* init_client()
{
    client = malloc(sizeof(client_t));
    if(client == NULL)
    {
        perror("malloc()");
        return NULL;
    }
    memset(client, 0, sizeof(client_t));

    if(init_socket())
    {
        printf("could not initialize win socket\n");
        return NULL;
    }

    if(init_socket_client(client))
    {
        printf("could not initialize client\n");
        return NULL;
    }

    join_acknowledge_event = malloc(sizeof(dynarray_t));
    dynarray_init(join_acknowledge_event, BASE_JA_SUBS, 8);
    
    return client;
}

void destroy_client()
{
    free(client->name);
    free(client);
}

int set_client_name(const char* name)
{
    size_t len = strlen(name);
    if(client->name == NULL)
    {
        client->name = malloc(len+1);
    }
    else
    {
        client->name = realloc(client->name, len+1);
    }

    if(client->name == NULL)
    {
        perror("malloc()");
        return -1;
    }
    memset(client->name, 0, len+1);
    memcpy(client->name, name, len);
    client->name[len] = '\0';
    return 0;
}

void subscribe_to_join_ack(JA_CALLBACK_TYPE(callback))
{
    dynarray_append(join_acknowledge_event, callback);
}

int connect_to_server()
{
    char data[MESSAGE_MAX_SIZE] = {0};
    unsigned int rid = 0;
    char* srid = (char*)&rid; 
    memcpy(data, srid, RID_SIZE);
    unsigned int command = COMMAND_CHALLENGE;
    command = btol((char*)&command, sizeof(unsigned int));
    char* scommand = (char*)&command;
    memcpy(&data[RID_SIZE], scommand, COMMAND_SIZE);
    memcpy(&data[RID_SIZE + COMMAND_SIZE], client->name, strlen(client->name));
    send_data_to(client->socket, "127.0.0.1", 9999, data, MESSAGE_MAX_SIZE);
    return 0;
}

void update_client()
{
    char* data = rec_data(client->socket, "127.0.0.1", 9999);
}

