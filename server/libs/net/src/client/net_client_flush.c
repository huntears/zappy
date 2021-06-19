/*
** EPITECH PROJECT, 2021
** NET_CLIENT_FLUSH
** File description:
** Net_client_flush function
*/

#include <unistd.h>

#include "net_server.h"

#include "net_client.h"

int nc_flush(net_client_t *net_client)
{
    int flushed =
        net_buffer_flush(&net_client->write_buffer, net_client->socket);

    if (flushed == -1 || net_client->write_buffer.length == 0)
        FD_CLR(net_client->socket, &net_client->net_server->need_write_fds);
    return flushed;
}