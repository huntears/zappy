/*
** EPITECH PROJECT, 2021
** NET_CLIENT
** File description:
** Net_client function
*/

#include <unistd.h>
#include <string.h>

#include "get_next_something.h"

#include "net_socket.h"
#include "net_client.h"

net_client_t *nc_create(net_server_t *net_server, int socket)
{
    net_client_t *net_client = malloc(sizeof(net_client_t));

    if (!net_client)
        return NULL;
    memset(net_client, 0, sizeof(net_client_t));
    net_client->net_server = net_server;
    net_client->socket = socket;
    net_client->disconnected = false;
    return net_client;
}

void *nc_destroy(net_client_t *net_client)
{
    if (!net_client)
        return NULL;
    if (net_client->socket != -1)
        gns_clear_socket(net_client->socket);
    if (socket_is_valid(net_client->socket))
        close_socket(net_client->socket);
    if (net_client->custom_data && net_client->custom_destructor)
        net_client->custom_destructor(net_client->custom_data);
    if (net_client->write_buffer.buffer)
        free(net_client->write_buffer.buffer);
    free(net_client);
    return NULL;
}