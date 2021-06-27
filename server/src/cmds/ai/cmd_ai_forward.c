/*
** EPITECH PROJECT, 2021
** CMD_AI_FORWARD
** File description:
** CMD_ai_forward function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

static void move_ai(
    zappy_server_t *server, zappy_client_t *client, int x, int y)
{
    zappy_ai_t *ai = client->ai;

    map_get_chunk(server->map, client->ai->x, client->ai->y)->nb_players--;
    ai->x = MOD(ai->x + x, server->map->width);
    ai->y = MOD(ai->y + y, server->map->height);
    map_get_chunk(server->map, client->ai->x, client->ai->y)->nb_players++;
}

void cmd_ai_forward(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    zappy_ai_t *ai = client->ai;

    UNUSED(line);
    switch (ai->direction) {
    case UP:
        move_ai(server, client, 0, -1);
        break;
    case RIGHT:
        move_ai(server, client, 1, 0);
        break;
    case DOWN:
        move_ai(server, client, 0, 1);
        break;
    case LEFT:
        move_ai(server, client, -1, 0);
        break;
    }
    zc_send_line(client, AI_OK);
    send_gui_ppo(server, client);
}