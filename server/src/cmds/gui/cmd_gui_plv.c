/*
** EPITECH PROJECT, 2021
** CMD_GUI_PLV
** File description:
** CMD_gui_bct_plv function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_gui_plv(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    uint64_t id;
    char after;

    if (sscanf(line, "plv %zu%c", &id, &after) != 1) {
        zc_send_line(client, GUI_KO_ARGS);
        return;
    }
    ITERATE_AIS(ai, server)
    {
        if (ai->ai->id == id) {
            send_gui_plv_to(client, ai);
            return;
        }
    }
    zc_send_line(client, GUI_KO_ARGS);
}