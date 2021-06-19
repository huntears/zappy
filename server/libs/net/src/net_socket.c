/*
** EPITECH PROJECT, 2021
** NET_SOCKET
** File description:
** Net_socket function
*/

#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "net_socket.h"

int create_socket(int domain, int type)
{
    int socket_fd = socket(domain, type, 0);

    if (socket_fd == -1)
    {
        fprintf(stderr, "Can not create socket");
        return -1;
    }
    return socket_fd;
}

bool bind_socket(int socket_fd, sa_family_t domain,
    uint16_t port, address_t *addr)
{
    socklen_t addr_size = sizeof(sockaddr_in_t);

    memset(addr, 0, sizeof(sockaddr_in_t));
    addr->sa_in.sin_family = domain;
    addr->sa_in.sin_port = htons(port);
    addr->sa_in.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(socket_fd, &addr->sa, addr_size) == -1)
    {
        perror("Bind failed");
        return false;
    }
    if (port == 0)
        if (getsockname(socket_fd, &addr->sa, &addr_size) == -1)
        {
            perror("Getsockname failed");
            return false;
        }
    return true;
}

bool listen_socket(int socket_fd)
{
    if (listen(socket_fd, SOMAXCONN) == -1)
    {
        perror("Listen failed");
        return false;
    }
    return true;
}

bool close_socket(int socket_fd)
{
    if (close(socket_fd) == -1)
    {
        perror("Close failed");
        return false;
    }
    return true;
}

int socket_is_valid(int socket_fd)
{
    if (socket_fd == -1)
        return false;
    return true;
}
