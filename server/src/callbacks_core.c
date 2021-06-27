/*
** EPITECH PROJECT, 2021
** CMDS_CORE
** File description:
** Cmds_core function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "net/gns/get_next_line.h"

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_client.h"
#include "zappy_server.h"

ns_status_e on_accept(net_server_t *net_server, net_client_t *net_client)
{
    zappy_server_t *zappy_server = (zappy_server_t *) net_server->custom_data;
    zappy_client_t *zappy_client = zappy_client_create(net_client);

    UNUSED(net_server), UNUSED(net_client);
    if (!zappy_client) {
        printf("Can not create zappy_client: memory exhausted\n");
        return NS_CLOSE_CLIENT;
    }
    net_client->custom_data = zappy_client;
    net_client->custom_destructor = (void *(*) (void *) ) zappy_client_destroy;
    return on_client_connect(zappy_server, zappy_client);
}

static ns_status_e on_ready_loop(
    net_server_t *net_server, net_client_t *net_client)
{
    zappy_server_t *zappy_server = (zappy_server_t *) net_server->custom_data;
    zappy_client_t *zappy_client = (zappy_client_t *) net_client->custom_data;
    ns_status_e return_value = NS_OK;
    char *line;

    line = gnl_extract_next_line(net_client->socket);
    if (!line)
        return NS_OK;
    return_value = on_client_recv_line(zappy_server, zappy_client, line);
    free(line);
    if (return_value == NS_OK)
        return on_ready_loop(net_server, net_client);
    return return_value;
}

ns_status_e on_ready(net_server_t *net_server, net_client_t *net_client)
{
    zappy_server_t *zappy_server = (zappy_server_t *) net_server->custom_data;
    zappy_client_t *zappy_client = (zappy_client_t *) net_client->custom_data;
    ns_status_e return_value = NS_OK;
    int read_len;
    char *line;

    line = gnl(net_client->socket, &read_len);
    if (read_len <= 0) {
        if (line)
            free(line);
        return (read_len == -1) ? NS_CLOSE_CLIENT : NS_DISCONNECT_CLIENT;
    }
    if (!line)
        return NS_OK;
    return_value = on_client_recv_line(zappy_server, zappy_client, line);
    free(line);
    if (return_value == NS_OK)
        return on_ready_loop(net_server, net_client);
    return return_value;
}

ns_status_e on_disconnect(net_server_t *net_server, net_client_t *net_client)
{
    zappy_server_t *zappy_server = (zappy_server_t *) net_server->custom_data;
    zappy_client_t *zappy_client = (zappy_client_t *) net_client->custom_data;

    return on_client_disconnect(zappy_server, zappy_client);
}

void on_timeval(net_server_t *net_server)
{
    zappy_server_t *zappy_server = (zappy_server_t *) net_server->custom_data;

    on_server_timeval(zappy_server);
}