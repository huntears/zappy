/*
** EPITECH PROJECT, 2021
** NET_SERVER_ACCEPT_ONE
** File description:
** Net_server_accept_one function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"

#include "interval.h"
#include "net_socket.h"

#include "net_server.h"

static void add_client_extend_interval(
    net_server_t *net_server, net_client_t *client)
{
    ns_add_client(net_server, client);
    FD_SET(client->socket, &net_server->need_read_fds);
    extend_interval(&net_server->socket_interval, client->socket);
}

bool ns_accept_one(net_server_t *ns)
{
    int new_socket;
    socklen_t len = sizeof(sockaddr_t);
    sockaddr_t addr;
    net_client_t *client = NULL;

    printf("Wait accept socket on: %d\n", ntohs(ns->addr.sa_in.sin_port));
    new_socket = accept(ns->socket, (struct sockaddr *) &addr, &len);
    if (new_socket == -1) {
        perror("Accept failed");
        return false;
    }
    printf("Client accepted on: %d\n", ntohs(ns->addr.sa_in.sin_port));
    client = nc_create(ns, new_socket);
    if (!client) {
        fprintf(stderr, "Can not create net_client: memory exhausted\n");
        close_socket(new_socket);
        return false;
    }
    add_client_extend_interval(ns, client);
    return true;
}