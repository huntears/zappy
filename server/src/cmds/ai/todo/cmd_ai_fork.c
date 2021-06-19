/*
** EPITECH PROJECT, 2021
** CMD_AI_FORK
** File description:
** CMD_ai_fork function
*/

#include "tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_ai_pre_fork(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    UNUSED(server), UNUSED(client), UNUSED(line);
    client->ai->is_fork = true;
}

void cmd_ai_fork(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    team_add_egg(client->ai->team_endpoint, client->ai->x, client->ai->y);
    client->ai->is_fork = false;
    zc_send_line(client, AI_OK);
}