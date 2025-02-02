#include <stdio.h>
#include <math.h>
#include <string.h>
#include "tictactoe_server.h"

void tick(server_t* server);
size_t ltob(const char* buffer, const size_t typesize);
char* num_to_str(const size_t num, const size_t base);
void kick_player(server_t* server, const char* addr_port_couple);

server_t* init_server()
{
    server_t* server = malloc(sizeof(server_t));

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

void start_server(server_t* server)
{
    printf("waiting for packets...\n");

    for(;;)
    {
        tick(server);
    }
}

void tick(server_t* server)
{
    char buffer[28];
    struct sockaddr_in sender_in;
    int sender_in_size = sizeof(sender_in);
    int len = recvfrom(server->socket, buffer, 28, 0, (struct sockaddr*)&sender_in, &sender_in_size);
    if (len < 0)
    {
        return;
    }
    char addr_as_string[64];
    inet_ntop(AF_INET, &sender_in.sin_addr, addr_as_string, 64);
    int rid = ltob(buffer, sizeof(int));
    int command = ltob(&buffer[4], sizeof(int));
    if(command == COMMAND_JOIN)
    {
        char* entry = malloc(32);
        size_t addr_len = strlen(addr_as_string);
        memcpy(entry, addr_as_string, addr_len);
        memcpy(&entry[addr_len], ":", 1);
        char* port = num_to_str(ntohs(sender_in.sin_port), 10);
        memcpy(&entry[addr_len+1], port, strlen(port));
        printf("%s\n", entry);
        if(!dict_contains_key(server->players, entry))
        {   
            printf("kicking player\n");
            kick_player(server, entry);
            return;
        }
        printf("adding player\n");
        player_t* new_player = init_player(&buffer[8]);
        dict_add(server->players, entry, new_player); 
    }
}

void kick_player(server_t* server, const char* addr_port_couple)
{
    player_t* bad_player = (player_t*)dict_get_value_by_key(server->players, addr_port_couple);
    if(!dict_remove(server->players, addr_port_couple))
    {
        printf("removed player: %s from server\n", bad_player->name);
    }
}

size_t ltob(const char* buff, const size_t typesize)
{
    size_t num = 0;

    for(size_t i = 0; i < typesize; i++)
    {   
        unsigned int to_shift = (unsigned int)buff[i];
        num += (to_shift << ((typesize - i - 1) * 8));
    }
    
    return num;
}

char* num_to_str(const size_t num, const size_t base)
{
    size_t digits = 0;
    size_t temp_num = num;
    do
    {
        temp_num = temp_num / base;
        digits++;
    }while(temp_num != 0);

    char* str = malloc(sizeof(char)*digits+1);
    memset(str, 0, digits+1);

    size_t curr_num = num;
    for(size_t i = 0; i < digits; i++)
    {
        size_t base_pow = (pow(base, digits - i - 1));
        size_t digit = num / base_pow;
        curr_num -= digit * base_pow;
        char ch;
        switch(digit)
        {
            case 0:
                ch = '0';
                break;
            case 1:
                ch = '1';
                break;
            case 2:
                ch = '2';
                break;
            case 3:
                ch = '3';
                break;
            case 4:
                ch = '4';
                break;
            case 5:
                ch = '5';
                break;
            case 6:
                ch = '6';
                break;
            case 7:
                ch = '7';
                break;
            case 8:
                ch = '8';
                break;
            case 9:
                ch = '9';
                break;
            default:
                break;
        }
        str[i] = ch;
    }

    str[digits+1] = '\0';

    return str;
}