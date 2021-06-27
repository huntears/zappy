/*
** EPITECH PROJECT, 2021
** ZAPPY_SERVER
** File description:
** Zappy_server header
*/

#ifndef ZAPPY_SERVER_H_
#define ZAPPY_SERVER_H_

#include "net/net_client.h"
#include "net/net_server.h"

#include "opt.h"

#include "map.h"
#include "teams.h"
#include "zappy_client.h"

typedef struct zappy_server {
    net_server_t *net_server;
    map_t *map;
    team_t **teams;
    uint64_t frequency;
} zappy_server_t;

#define ITERATE_CLIENTS(client, server)                                        \
    zappy_client_t *client;                                                    \
    LIST_ITERATE(it, server->net_server->clients)                              \
    if ((client = ((net_client_t *) it->data)->custom_data))

#define ITERATE_AIS(_ai, server)                                               \
    zappy_client_t *_ai;                                                       \
    LIST_ITERATE(it, server->net_server->clients)                              \
    if ((_ai = ((net_client_t *) it->data)->custom_data)                       \
        && _ai->type == CLIENT_AI && _ai->ai->is_alive)

#define ITERATE_AIS_N(_ai, server, id)                                         \
    zappy_client_t *_ai;                                                       \
    LIST_ITERATE_N(it, server->net_server->clients, id)                        \
    if ((_ai = ((net_client_t *) it->data)->custom_data)                       \
        && _ai->type == CLIENT_AI && _ai->ai->is_alive)

#define ITERATE_GUIS(gui, server)                                              \
    zappy_client_t *gui;                                                       \
    LIST_ITERATE(it, server->net_server->clients)                              \
    if ((gui = ((net_client_t *) it->data)->custom_data)                       \
        && gui->type == CLIENT_GRAPHIC)

#define ITERATE_EGGS(egg, eggs)                                                \
    egg_t *egg;                                                                \
    LIST_ITERATE(it, eggs)                                                     \
    if ((egg = it->data))

// create / destroy
zappy_server_t *zappy_server_create(struct opts *opts);
void *zappy_server_destroy(zappy_server_t *server);

// net callbacks
ns_status_e on_accept(net_server_t *net_server, net_client_t *net_client);
ns_status_e on_ready(net_server_t *net_server, net_client_t *net_client);
ns_status_e on_disconnect(net_server_t *net_server, net_client_t *net_client);
void on_close(net_server_t *net_server, net_client_t *net_client);
void on_timeval(net_server_t *net_server);

#endif /* !ZAPPY_SERVER_H_ */