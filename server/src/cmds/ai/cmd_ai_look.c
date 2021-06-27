/*
** EPITECH PROJECT, 2021
** CMD_AI_LOOK
** File description:
** CMD_ai_look function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

static chunk_t *get_chunk(
    zappy_server_t *server, zappy_client_t *client, int layer, int col)
{
    int x = client->ai->x;
    int y = client->ai->y;

    if (client->ai->direction == UP) {
        x -= layer;
        y += col;
    }
    if (client->ai->direction == RIGHT) {
        x += col;
        y += layer;
    }
    if (client->ai->direction == DOWN) {
        x += layer;
        y -= col;
    }
    if (client->ai->direction == LEFT) {
        x -= col;
        y -= layer;
    }
    return map_get_chunk(server->map, x, y);
}

static void show_chunk_content(
    zappy_server_t *server, zappy_client_t *client, int layer, int col)
{
    chunk_t *chunk = get_chunk(server, client, layer, col);
    bool print_separator = false;

    for (size_t k = 0; k < chunk->nb_players; k++) {
        zc_send(client, print_separator ? " " : "");
        print_separator = true;
        zc_send(client, "player");
    }
    for (size_t object_type = 0; object_type < NB_OBJECTS; object_type++) {
        for (size_t k = 0; k < chunk->objects[object_type]; k++) {
            zc_send(client, print_separator ? " " : "");
            print_separator = true;
            zc_send(client, object_to_string(object_type));
        }
    }
}

static void show_layer(
    zappy_server_t *server, zappy_client_t *client, int layer)
{
    for (int col = -layer; col <= layer; col++) {
        show_chunk_content(server, client, layer, col);
        if ((layer != 1 + (int) client->ai->level) || (col != layer))
            zc_send(client, ", ");
    }
}

void cmd_ai_look(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    UNUSED(line);
    zc_send(client, "[");
    for (int layer = 0; layer < 2 + (int) client->ai->level; layer++)
        show_layer(server, client, layer);
    zc_send_line(client, "]");
}