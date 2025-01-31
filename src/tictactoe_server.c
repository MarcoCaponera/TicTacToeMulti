#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <stdio.h>

int s;

int init_server()
{
#ifdef _WIN32
    WSADATA wsa_data;
    if(WSAStartup(0x0202, &wsa_data))
    {
        printf("unable to initialize winsock2 \n");
        return -1;
    }
#endif

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(s < 0)
    {
        printf("unable to initialize the UDP socket \n");
        return -1;
    }

    // creation of the address
    struct sockaddr_in sin;
    inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr); // creation of a big endian 32 bit address
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9999); // conversion to big endian

    if(bind(s, (struct sockaddr*)&sin, sizeof(sin)))
    {
        printf("unable to bind UDP socket\n");
        return -1;
    }

    return 0;
}