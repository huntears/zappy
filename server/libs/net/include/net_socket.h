/*
** EPITECH PROJECT, 2021
** NET_SOCKET
** File description:
** Net_socket header
*/

#ifndef NET_SOCKET_H_
#define NET_SOCKET_H_

#include <netinet/ip.h>
#include <stdbool.h>

typedef struct sockaddr_in sockaddr_in_t;
typedef struct sockaddr sockaddr_t;

typedef union address {
    sockaddr_t sa;
    sockaddr_in_t sa_in;
} address_t;

int create_socket(int domain, int type);
bool bind_socket(int socket_fd, sa_family_t domain,
    uint16_t port, address_t *addr);
bool listen_socket(int socket_fd);
bool close_socket(int socket_fd);
int socket_is_valid(int socket_fd);

#endif /* !NET_SOCKET_H_ */