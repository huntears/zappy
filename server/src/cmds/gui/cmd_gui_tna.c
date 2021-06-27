/*
** EPITECH PROJECT, 2021
** CMD_GUI_TNA
** File description:
** CMD_gui_bct_tna function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_gui_tna(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    UNUSED(line);
    for (size_t team_id = 0; server->teams[team_id]; team_id++) {
        zc_send(client, "tna %s\n", server->teams[team_id]->name);
    }
}