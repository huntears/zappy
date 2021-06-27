/*
** EPITECH PROJECT, 2021
** CMD_AI_CHEAT_LEVEL_UP
** File description:
** Cmd_ai_cheat_level_up function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_ai_cheat_level_up(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    UNUSED(server), UNUSED(line);
    if (client->ai->level == 7) {
        zc_send_line(client, AI_KO);
        return;
    }
    client->ai->team_endpoint->levels[client->ai->level]--;
    client->ai->level++;
    client->ai->team_endpoint->levels[client->ai->level]++;
    zc_send(client, "Current level: %d\n", client->ai->level + 1);
}