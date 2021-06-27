/*
** EPITECH PROJECT, 2021
** CALLBACKS
** File description:
** Callbacks function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_client.h"
#include "zappy_server.h"

ns_status_e on_client_connect(
    zappy_server_t *zappy_server, zappy_client_t *zappy_client)
{
    UNUSED(zappy_server);
    zc_send_line(zappy_client, "WELCOME");
    return NS_OK;
}

ns_status_e on_client_recv_line(zappy_server_t *zappy_server,
    zappy_client_t *zappy_client, const char *line)
{
    if (strlen(line) == 0)
        return NS_OK;
    if (zappy_client->type == CLIENT_UNKNOWN) {
        if (!client_chose_team(zappy_server, zappy_client, line))
            zc_send_line(zappy_client, AI_KO);
        return NS_OK;
    }
    if (zappy_client->type == CLIENT_AI)
        store_cmd_ai(zappy_client, line);
    else
        cmd_gui(zappy_server, zappy_client, line);
    return NS_OK;
}

ns_status_e on_client_disconnect(
    zappy_server_t *zappy_server, zappy_client_t *zappy_client)
{
    UNUSED(zappy_server), UNUSED(zappy_client);
    if (zappy_client->type == CLIENT_AI) {
        if (zappy_client->ai->is_alive)
            zappy_ai_die(zappy_client, zappy_server);
        printf("AI %lu disconnected\n", zappy_client->ai->id);
    } else if (zappy_client->type == CLIENT_GRAPHIC) {
        printf("GUI disconnected\n");
    }
    return NS_OK;
}

void on_server_timeval(zappy_server_t *zappy_server)
{
    ITERATE_AIS(client_ai, zappy_server)
    {
        zappy_ai_consume_time(zappy_server, client_ai, 1);
    }
    for (size_t team_id = 0; zappy_server->teams[team_id]; team_id++) {
        team_consume_time(zappy_server, zappy_server->teams[team_id], 1);
    }
    map_spawn_objects(zappy_server->map, zappy_server);
}