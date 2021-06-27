/*
** EPITECH PROJECT, 2021
** CMD_GUI_MSZ
** File description:
** CMD_gui_bct_msz function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_gui_msz(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    UNUSED(line);
    zc_send(client, "msz %zu %zu\n", server->map->width, server->map->height);
}