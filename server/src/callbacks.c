/*
** EPITECH PROJECT, 2021
** CALLBACKS
** File description:
** Callbacks function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

#include "server_cmds.h"
#include "zappy_client.h"
#include "zappy_server.h"

ns_status_e on_client_connect(
    zappy_server_t *zappy_server, zappy_client_t *zappy_client)
{
    UNUSED(zappy_server);
    printf("Client connect\n");
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
        cmd_ai(zappy_server, zappy_client, line);
    else
        cmd_gui(zappy_server, zappy_client, line);
    return NS_OK;
}

ns_status_e on_client_disconnect(
    zappy_server_t *zappy_server, zappy_client_t *zappy_client)
{
    UNUSED(zappy_server), UNUSED(zappy_client);
    if (zappy_client->type == CLIENT_AI && zappy_client->ai->is_alive)
        zappy_ai_die(zappy_client);
    printf("Client disconnected\n");
    return NS_OK;
}

void on_server_timeval(zappy_server_t *zappy_server)
{
    ITERATE_AIS(client_ai, zappy_server)
    {
        zappy_ai_consume_time(zappy_server, client_ai, 1);
    }
}