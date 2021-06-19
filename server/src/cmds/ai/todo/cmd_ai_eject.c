/*
** EPITECH PROJECT, 2021
** CMD_AI_EJECT
** File description:
** CMD_ai_eject function
*/

#include "tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_ai_eject(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    chunk_t *chunk = map_get_chunk(server->map, client->ai->x, client->ai->y);

    UNUSED(line);
    if (chunk->nb_players == 0) {
        zc_send_line(client, AI_KO);
        return;
    }
    zc_send_line(client, AI_OK);
}