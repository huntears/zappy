/*
** EPITECH PROJECT, 2021
** ZAPPY_AI
** File description:
** Zappy_ai function
*/

#include <stdlib.h>
#include <string.h>

#include "server_cmds.h"
#include "zappy_ai.h"
#include "zappy_server.h"

static void zappy_ai_init(zappy_ai_t *zappy_ai, zappy_server_t *server,
    team_t *team_endpoint, size_t id)
{
    zappy_ai->team_endpoint = team_endpoint;
    zappy_ai->id = id;
    zappy_ai->is_alive = true;
    zappy_ai->level = 0;
    zappy_ai->x = rand() % server->map->width;
    zappy_ai->y = rand() % server->map->height;
    zappy_ai->direction = (enum direction)(rand() % 4);
    zappy_ai->inventory[FOOD] = 9;
    zappy_ai->remaining_time = REMAINING_TIME_PER_FOOD;
    map_get_chunk(server->map, zappy_ai->x, zappy_ai->y)->nb_players++;
    zappy_ai->team_endpoint->nb_ai++;
    zappy_ai->team_endpoint->levels[zappy_ai->level]++;
    zappy_ai->commands.time_before_cmd_execution = -1;
}

zappy_ai_t *zappy_ai_create(
    zappy_server_t *server, team_t *team_endpoint, size_t id)
{
    zappy_ai_t *zappy_ai = malloc(sizeof(zappy_ai_t));

    if (!zappy_ai)
        return NULL;
    memset(zappy_ai, 0, sizeof(zappy_ai_t));
    zappy_ai->commands.commands_queue = list_create(&free);
    if (!zappy_ai->commands.commands_queue)
        return zappy_ai_destroy(zappy_ai);
    zappy_ai_init(zappy_ai, server, team_endpoint, id);
    return zappy_ai;
}

void *zappy_ai_destroy(zappy_ai_t *zappy_ai)
{
    if (!zappy_ai)
        return NULL;
    if (zappy_ai->commands.commands_queue)
        list_destroy(zappy_ai->commands.commands_queue);
    free(zappy_ai);
    return NULL;
}

void zappy_ai_die(zappy_client_t *client, zappy_server_t *server)
{
    client->ai->is_alive = false;
    client->ai->team_endpoint->nb_ai--;
    map_get_chunk(server->map, client->ai->x, client->ai->y)->nb_players--;
    client->ai->team_endpoint->levels[client->ai->level]--;
    zc_send_line(client, "dead");
    send_gui_pdi(server, client->ai->id);
    client->net_client->need_disconnection = true;
}