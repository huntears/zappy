/*
** EPITECH PROJECT, 2021
** CMD_AI_TAKE
** File description:
** CMD_ai_take function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

static enum object_type extract_object_type(const char *line)
{
    char buff_object_name[100];
    char after;

    if (sscanf(line, "Take %99s%c", buff_object_name, &after) != 1)
        return UNKNOWN_OBJECT;
    return string_to_object(buff_object_name);
}

void cmd_ai_take(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    enum object_type object = extract_object_type(line);
    chunk_t *chunk = map_get_chunk(server->map, client->ai->x, client->ai->y);

    if (object == UNKNOWN_OBJECT || chunk->objects[object] == 0
        || client->ai->inventory[object] == UINT64_MAX) {
        zc_send_line(client, AI_KO);
        return;
    }
    chunk->objects[object]--;
    server->map->object_count[object]--;
    client->ai->inventory[object]++;
    zc_send_line(client, AI_OK);
    send_gui_pgt(server, client->ai->id, object);
    send_gui_pin(server, client);
    send_gui_bct(server, client->ai->x, client->ai->y);
}