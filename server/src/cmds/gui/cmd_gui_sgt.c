/*
** EPITECH PROJECT, 2021
** CMD_GUI_SGT
** File description:
** CMD_gui_bct_sgt function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_gui_sgt(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    UNUSED(line);
    zc_send(client, "sgt %lu\n", server->frequency);
}