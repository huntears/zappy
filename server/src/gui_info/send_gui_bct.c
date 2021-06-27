/*
** EPITECH PROJECT, 2021
** SEND_GUI_BCT
** File description:
** Send_gui_bct function
*/

#include "zappy_server.h"

void send_gui_bct_to(zappy_client_t *gui, zappy_server_t *server, int x, int y)
{
    chunk_t *chunk;

    x = MOD(x, server->map->width);
    y = MOD(y, server->map->height);
    chunk = map_get_chunk(server->map, x, y);
    zc_send(gui, "bct %d %d %zu %zu %zu %zu %zu %zu %zu\n", x, y,
        chunk->objects[FOOD], chunk->objects[LINEMATE],
        chunk->objects[DERAUMERE], chunk->objects[SIBUR],
        chunk->objects[MENDIANE], chunk->objects[PHIRAS],
        chunk->objects[THYSTAME]);
}

void send_gui_bct(zappy_server_t *server, int x, int y)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_bct_to(gui, server, x, y);
    }
}