/*
** EPITECH PROJECT, 2021
** CMD_AI_INCANTATION
** File description:
** CMD_ai_incantation function
*/

#include "tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

static const struct incant_requirements requirements[] = {
    { 1, { 1, 0, 0, 0, 0, 0 } }, // 1->2
    { 2, { 1, 1, 1, 0, 0, 0 } }, // 2->3
    { 2, { 2, 0, 1, 0, 2, 0 } }, // 3->4
    { 4, { 1, 1, 2, 0, 1, 0 } }, // 4->5
    { 4, { 1, 2, 1, 3, 0, 0 } }, // 5->6
    { 6, { 1, 2, 3, 0, 1, 0 } }, // 6->7
    { 6, { 2, 2, 2, 2, 2, 1 } }, // 7->8
};

static bool can_incant(zappy_server_t *server, zappy_client_t *client)
{
    chunk_t *chunk = map_get_chunk(server->map, client->ai->x, client->ai->y);

    if (client->ai->level == 7)
        return false;
    if (chunk->nb_players != requirements[client->ai->level].nb_of_players)
        return false;
    for (size_t object_id = 1; object_id < NB_OBJECTS; object_id++) {
        if (chunk->objects[object_id]
            != requirements[client->ai->level].objects[object_id - 1]) {
            return false;
        }
    }
    return true;
}

void cmd_ai_pre_incantation(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    UNUSED(line);
    client->ai->is_incantated = true;
    if (!can_incant(server, client)) {
        client->ai->pre_incantation_success = false;
        zc_send_line(client, AI_KO);
        return;
    }
    client->ai->pre_incantation_success = true;
    zc_send_line(client, "Elevation underway");
}

void cmd_ai_incantation(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    UNUSED(line);
    client->ai->is_incantated = false;
    if (!client->ai->pre_incantation_success || !can_incant(server, client)) {
        zc_send_line(client, AI_KO);
        return;
    }
    client->ai->team_endpoint->levels[client->ai->level]--;
    client->ai->level++;
    client->ai->team_endpoint->levels[client->ai->level]++;
    zc_send(client, "Current level: %d\n", client->ai->level + 1);
}