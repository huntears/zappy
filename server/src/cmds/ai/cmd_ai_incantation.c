/*
** EPITECH PROJECT, 2021
** CMD_AI_INCANTATION
** File description:
** CMD_ai_incantation function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

static const struct incant_requirements requirements[] = {
    { 1, { 1, 0, 0, 0, 0, 0 } },
    { 2, { 1, 1, 1, 0, 0, 0 } },
    { 2, { 2, 0, 1, 0, 2, 0 } },
    { 4, { 1, 1, 2, 0, 1, 0 } },
    { 4, { 1, 2, 1, 3, 0, 0 } },
    { 6, { 1, 2, 3, 0, 1, 0 } },
    { 6, { 2, 2, 2, 2, 2, 1 } },
};

static bool can_incant(zappy_server_t *server, zappy_client_t *client)
{
    chunk_t *chunk = map_get_chunk(server->map, client->ai->x, client->ai->y);

    if (client->ai->level >= 7)
        return false;
    if (chunk->nb_players != requirements[client->ai->level].nb_of_players)
        return false;
    for (size_t object_id = 1; object_id < NB_OBJECTS; object_id++) {
        if (chunk->objects[object_id]
            != requirements[client->ai->level].objects[object_id - 1]) {
            return false;
        }
    }
    ITERATE_AIS(ai, server)
    {
        if (ai->ai->x != client->ai->x || ai->ai->y != client->ai->y)
            continue;
        if (ai->ai->level != client->ai->level)
            return false;
    }
    return true;
}

void cmd_ai_pre_incantation(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    UNUSED(line);
    client->ai->is_incantated = true;
    send_gui_pic(server, client);
    if (!can_incant(server, client)) {
        client->ai->pre_incantation_success = false;
        zc_send_line(client, AI_KO);
        return;
    }
    client->ai->pre_incantation_success = true;
    ITERATE_AIS(ai, server)
    {
        if (ai->ai->x == client->ai->x && ai->ai->y == client->ai->y) {
            zc_send_line(ai, "Elevation underway");
        }
    }
}

void cmd_ai_incantation(zappy_server_t *server, zappy_client_t *client,
    __attribute__((unused)) const char *line)
{
    client->ai->is_incantated = false;
    if (!client->ai->pre_incantation_success || !can_incant(server, client)) {
        send_gui_pie(server, client->ai->x, client->ai->y, false);
        zc_send_line(client, AI_KO);
        return;
    }
    send_gui_pie(server, client->ai->x, client->ai->y, true);
    ITERATE_AIS(ai, server) {
        if (ai->ai->x == client->ai->x && ai->ai->y == client->ai->y) {
            ai->ai->team_endpoint->levels[ai->ai->level]--;
            ai->ai->level++;
            ai->ai->team_endpoint->levels[ai->ai->level]++;
            zc_send(ai, "Current level: %d\n", ai->ai->level + 1);
            send_gui_plv(server, ai);
        }
    }
    if (client->ai->team_endpoint->levels[7]) {
        server->net_server->running = false;
        send_gui_seg(server, client->ai->team_endpoint->name);
    }
}