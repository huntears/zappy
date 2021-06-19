/*
** EPITECH PROJECT, 2021
** ZAPPY_SERVER
** File description:
** Zappy_server function
*/

#include <stdlib.h>
#include <string.h>

#include "opt.h"

#include "server_cmds.h"
#include "zappy_server.h"

static const ns_callbacks_t net_server_cmds = {
    .on_accept = on_accept,
    .on_ready = on_ready,
    .on_disconnect = on_disconnect,
    .on_close = NULL,
};

zappy_server_t *zappy_server_create(struct opts *opts)
{
    zappy_server_t *server = malloc(sizeof(zappy_server_t));

    if (!server)
        return NULL;
    memset(server, 0, sizeof(zappy_server_t));
    server->net_server = ns_create(AF_INET, SOCK_STREAM, opts->port);
    if (!server->net_server)
        return zappy_server_destroy(server);
    ns_set_callbacks(server->net_server, net_server_cmds);
    server->net_server->custom_data = server;
    server->teams = teams_create(opts->names, opts->max_clients);
    server->frequency = opts->frequency;
    server->map = map_create(opts->width, opts->height);
    if (!server->map || !server->teams)
        return zappy_server_destroy(server);
    return server;
}

void *zappy_server_destroy(zappy_server_t *server)
{
    if (!server)
        return NULL;
    if (server->net_server)
        ns_destroy(server->net_server);
    if (server->map)
        map_destroy(server->map);
    if (server->teams)
        teams_destroy(server->teams);
    free(server);
    return NULL;
}