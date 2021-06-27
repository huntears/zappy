/*
** EPITECH PROJECT, 2021
** CMD_AI_CHEAT_TELEPORTATION
** File description:
** Cmd_ai_cheat_teleportation function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_ai_cheat_teleportation(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    int x;
    int y;
    char after;

    if (sscanf(line, "Cheat_teleportation %d %d%c", &x, &y, &after) != 2) {
        zc_send_line(client, AI_KO);
        return;
    }
    map_get_chunk(server->map, client->ai->x, client->ai->y)->nb_players--;
    client->ai->x = MOD(x, server->map->width);
    client->ai->y = MOD(y, server->map->height);
    map_get_chunk(server->map, client->ai->x, client->ai->y)->nb_players++;
    zc_send_line(client, AI_OK);
    send_gui_ppo(server, client);
}