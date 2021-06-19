/*
** EPITECH PROJECT, 2021
** CMD_AI_BROADCAST
** File description:
** CMD_ai_broadcast function
*/

#include "tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_ai_broadcast(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    UNUSED(server), UNUSED(line);
    zc_send_line(client, AI_OK);
}