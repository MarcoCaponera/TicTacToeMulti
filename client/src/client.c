#ifdef _WIN32
 #include <WinSock2.h>
 #include <ws2tcpip.h>
 #include <windows.h>
 #else
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>
 #include <unistd.h>
 #endif
 #include <stdio.h>

 #include "client.h"
 #include <string.h>
 #include <stdint.h>

 client_t* init_client()
 {
    client_t* client = malloc(sizeof(client_t));

    if(client == NULL)
    {
        perror("malloc()");
        return NULL;
    }

    memset(client, 0, sizeof(client_t));

 #ifdef _WIN32
    // this part is only required on Windows: it initializes the Winsock2 dll
    WSADATA wsa_data;
    if (WSAStartup(0x0202, &wsa_data))
    {
        printf("unable to initialize winsock2 \n");
        return NULL;
    }
 #endif
    client->socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (client->socket < 0)
    {
        printf("unable to initialize the UDP socket \n");
        return NULL;
    }
    struct sockaddr_in sin;
    inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr); // this will create a big endian 32 bit address
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9999); // converts 9999 to big endian

    memcpy(&client->sock_addr, &sin, sizeof(struct sockaddr_in));

    return client;
 }

 void destroy_client(client_t** client)
 {
    client_t* c = *client;
    free(c->name);
    free(c);
 }

 int set_client_name(client_t* client, const char* name)
 {
    size_t len = strlen(name);
    printf("len: %llu\n", len);
    client->name = malloc(len+1);
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