/*
** EPITECH PROJECT, 2021
** CMD_GUI_MCT
** File description:
** CMD_gui_bct_mct function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_gui_mct(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    UNUSED(line);
    for (size_t y = 0; y < server->map->height; y++)
        for (size_t x = 0; x < server->map->width; x++)
            send_gui_bct_to(client, server, x, y);
}