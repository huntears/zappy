/*
** EPITECH PROJECT, 2021
** NET_SERVER_CLIENT
** File description:
** Net_server_client function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#include "net_client.h"
#include "net_server.h"
#include "net_socket.h"

void ns_disconnect_client(net_server_t *net_server, net_client_t *net_client)
{
    bool is_disconnected = net_client->disconnected;

    net_client->disconnected = true;
    if (!is_disconnected)
        NS_CALLBACK(net_server, on_disconnect, net_client);
    if (!(net_client->write_buffer.length != 0
            && FD_ISSET(net_client->socket, &net_server->need_write_fds)))
        ns_remove_client(net_server, net_client);
}

bool ns_add_client(net_server_t *ns, net_client_t *net_client)
{
    if (!net_client)
        return false;
    if (list_add(ns->clients, net_client))
        return false;
    return true;
}

void ns_remove_client(net_server_t *net_server, net_client_t *net_client)
{
    int socket_fd = net_client->socket;

    if (!net_client->disconnected)
        NS_CALLBACK(net_server, on_disconnect, net_client);
    if (net_server->callbacks.on_close)
        net_server->callbacks.on_close(net_server, net_client);
    FD_CLR(socket_fd, &net_server->read_fds);
    FD_CLR(socket_fd, &net_server->write_fds);
    FD_CLR(socket_fd, &net_server->need_write_fds);
    FD_CLR(socket_fd, &net_server->need_read_fds);
    remove_fd_socket_from_interval(
        &net_server->socket_interval, &net_server->need_read_fds, socket_fd);
    list_remove_data(net_server->clients, net_client);
}

net_client_t *ns_get_client(net_server_t *net_server, int socket_fd)
{
    net_client_t *net_client;

    for (int k = 0; k < net_server->clients->size; k++) {
        net_client = list_get(net_server->clients, k);
        if (net_client->socket == socket_fd)
            return net_client;
    }
    fprintf(stderr, "Can not find client with socket_fd: %d\n", socket_fd);
    return NULL;
}

void ns_close_all_sockets(net_server_t *net_server)
{
    printf("Exit server on port: %d, close all sockets...\n",
        ntohs(net_server->addr.sa_in.sin_port));
    list_clear(net_server->clients);
    net_server->running = false;
}