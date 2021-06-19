/*
** EPITECH PROJECT, 2021
** CMD_AI_LEFT
** File description:
** CMD_ai_left function
*/

#include "tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_ai_left(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    zappy_ai_t *ai = client->ai;

    UNUSED(server), UNUSED(line);
    ai->direction = (enum direction)((ai->direction - 1) % 4);
    zc_send_line(client, AI_OK);
}