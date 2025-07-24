#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif 

#include "win_wrap.h"
#include <stdio.h>

int init_socket()
{

#ifdef _WIN32
    // this part is only required on Windows: it initializes the Winsock2 dll
    WSADATA wsa_data;
    if (WSAStartup(0x0202, &wsa_data))
    {
        printf("unable to initialize winsock2 \n");
        return -1;
    }
#endif

    return 0;
}

int init_socket_client(client_t* client)
{
    client->socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (client->socket < 0)
    {
        printf("unable to initialize the UDP socket \n");
        return -1;
    }
    client->addr_family = AF_INET;
    client->port = htons(9999);

    return 0;
}


void send_data_to(int socket, char* address, unsigned short port, char* data, size_t len)
{
    struct sockaddr_in sin;
    inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr); // this will create a big endian 32 bit address
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port); // converts 9999 to big endian
    sendto(socket, data, len, 0, (struct sockaddr*)&sin, sizeof(sin));
}

char* rec_data(int socket, char* address, unsigned short port)
{
    char buffer[4096];
    struct sockaddr_in sender_in;
    int sender_in_size = sizeof(sender_in);
    int len = recvfrom(socket, buffer, 4096, 0, (struct sockaddr*)&sender_in, &sender_in_size);
    if (len > 0)
    {
        char addr_as_string[64];
        inet_ntop(AF_INET, &sender_in.sin_addr, addr_as_string, 64);
        printf("received %d bytes from %s:%d\n", len, addr_as_string, ntohs(sender_in.sin_port));
        char* new_buff = malloc(4096);
        memcpy(new_buff, buffer, 4096);

        return new_buff;
    }

    return NULL;
}