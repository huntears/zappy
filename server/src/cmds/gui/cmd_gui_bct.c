/*
** EPITECH PROJECT, 2021
** CMD_GUI_BCT
** File description:
** CMD_gui_bct function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_gui_bct(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    int x;
    int y;
    char after;

    if (sscanf(line, "bct %d %d%c", &x, &y, &after) != 2) {
        zc_send_line(client, GUI_KO_ARGS);
        return;
    }
    send_gui_bct_to(client, server, x, y);
}