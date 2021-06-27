/*
** EPITECH PROJECT, 2021
** CMD_AI_EJECT
** File description:
** CMD_ai_eject function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

static void eject_ai_to(
    zappy_server_t *server, zappy_client_t *client, int x, int y)
{
    map_get_chunk(server->map, client->ai->x, client->ai->y)->nb_players--;
    client->ai->x = MOD(client->ai->x + x, server->map->width);
    client->ai->y = MOD(client->ai->y + y, server->map->height);
    map_get_chunk(server->map, client->ai->x, client->ai->y)->nb_players++;
}

static const size_t eject_dirs[] = { 1, 7, 5, 3 };

static void eject_ai(zappy_server_t *server, zappy_client_t *client,
    zappy_client_t *ejected_client)
{
    int eject_dir =
        MOD(client->ai->direction - ejected_client->ai->direction + 2, 4);

    switch (client->ai->direction) {
    case UP:
        eject_ai_to(server, ejected_client, -1, 0);
        break;
    case RIGHT:
        eject_ai_to(server, ejected_client, 0, 1);
        break;
    case DOWN:
        eject_ai_to(server, ejected_client, 1, 0);
        break;
    case LEFT:
        eject_ai_to(server, ejected_client, 0, -1);
        break;
    }
    zc_send(ejected_client, "eject: %d\n", eject_dirs[eject_dir]);
    send_gui_ppo(server, client);
}

void cmd_ai_eject(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    chunk_t *chunk = map_get_chunk(server->map, client->ai->x, client->ai->y);

    UNUSED(line);
    if (chunk->nb_players <= 1) {
        zc_send_line(client, AI_KO);
        return;
    }
    send_gui_pex(server, client->ai->id);
    ITERATE_AIS(ejected_client, server)
    {
        if (ejected_client->ai->x != client->ai->x
            || ejected_client->ai->y != client->ai->y)
            continue;
        if (client->ai->id == ejected_client->ai->id)
            continue;
        eject_ai(server, client, ejected_client);
    }
    zc_send_line(client, AI_OK);
}