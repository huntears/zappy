/*
** EPITECH PROJECT, 2021
** ZAPPY_AI
** File description:
** Zappy_ai function
*/

#include <stdlib.h>
#include <string.h>

#include "zappy_ai.h"
#include "zappy_server.h"

zappy_ai_t *zappy_ai_create(zappy_server_t *server, team_t *team_endpoint)
{
    zappy_ai_t *zappy_ai = malloc(sizeof(zappy_ai_t));

    if (!zappy_ai)
        return NULL;
    memset(zappy_ai, 0, sizeof(zappy_ai_t));
    zappy_ai->team_endpoint = team_endpoint;
    zappy_ai->commands_queue = list_create(&free);
    if (!zappy_ai->commands_queue)
        return zappy_ai_destroy(zappy_ai);
    zappy_ai->is_alive = true;
    zappy_ai->level = 0;
    zappy_ai->x = rand() % server->map->width;
    zappy_ai->y = rand() % server->map->height;
    zappy_ai->direction = (enum direction)(rand() % 4);
    zappy_ai->inventory[FOOD] = 9;
    zappy_ai->remaining_time = REMAINING_TIME_PER_FOOD;
    map_get_chunk(server->map, zappy_ai->x, zappy_ai->y)->nb_players++;
    team_endpoint->nb_ai++;
    team_endpoint->levels[zappy_ai->level]++;
    return zappy_ai;
}

void *zappy_ai_destroy(zappy_ai_t *zappy_ai)
{
    if (!zappy_ai)
        return NULL;
    if (zappy_ai->commands_queue)
        list_destroy(zappy_ai->commands_queue);
    free(zappy_ai);
    return NULL;
}

bool zappy_ai_consume_time(
    zappy_server_t *server, zappy_client_t *client, size_t consume_time)
{
    if (client->ai->remaining_time <= consume_time) {
        if (client->ai->inventory[FOOD] == 0) {
            client->ai->remaining_time = 0;
            client->ai->is_alive = false;
            zappy_ai_die(client);
        } else {
            client->ai->inventory[FOOD]--;
            client->ai->remaining_time += REMAINING_TIME_PER_FOOD;
            send_gui_pin(server, client);
            return zappy_ai_consume_time(server, client, consume_time);
        }
    } else
        client->ai->remaining_time -= consume_time;
    return client->ai->is_alive;
}

void zappy_ai_die(zappy_client_t *zappy_client)
{
    zappy_client->ai->team_endpoint->nb_ai--;
    zappy_client->ai->team_endpoint->levels[zappy_client->ai->level]--;
    zc_send_line(zappy_client, "dead");
    zappy_client->net_client->need_disconnection = true;
}