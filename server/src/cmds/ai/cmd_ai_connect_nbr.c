/*
** EPITECH PROJECT, 2021
** CMD_AI_CONNECT_NBR
** File description:
** CMD_ai_connect_nbr function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_ai_connect_nbr(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    UNUSED(server), UNUSED(line);
    zc_send(client, "%d\n", team_get_connect_nbr(client->ai->team_endpoint));
}