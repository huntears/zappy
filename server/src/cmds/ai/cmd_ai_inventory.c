/*
** EPITECH PROJECT, 2021
** CMD_AI_INVENTORY
** File description:
** CMD_ai_inventory function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_ai.h"
#include "zappy_server.h"

static const char INVENTORY_FORMAT[] =
    "[food %lu, linemate %lu, deraumere %lu, sibur %lu, mendiane %lu, phiras "
    "%lu, thystame %lu]\n";

void cmd_ai_inventory(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    size_t *inventory = client->ai->inventory;

    UNUSED(server), UNUSED(line);
    zc_send(client, INVENTORY_FORMAT, inventory[0], inventory[1], inventory[2],
        inventory[3], inventory[4], inventory[5], inventory[6]);
}