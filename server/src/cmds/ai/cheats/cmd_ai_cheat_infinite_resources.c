/*
** EPITECH PROJECT, 2021
** CMD_AI_CHEAT_INFINITE_RESOURCES
** File description:
** Cmd_ai_cheat_infinite_resources function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_ai_cheat_infinite_resources(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    size_t *inventory = client->ai->inventory;

    UNUSED(server), UNUSED(line);
    for (size_t object_id = 0; object_id < NB_OBJECTS; object_id++)
        inventory[object_id] = UINT64_MAX / 2llu;
    zc_send_line(client, AI_OK);
}