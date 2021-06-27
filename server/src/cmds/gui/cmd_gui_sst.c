/*
** EPITECH PROJECT, 2021
** CMD_GUI_SST
** File description:
** CMD_gui_bct_sst function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

void cmd_gui_sst(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    uint64_t frequency;
    char after;

    if (sscanf(line, "sst %lu%c", &frequency, &after) != 1 || frequency < 1
        || frequency > 100000) {
        zc_send_line(client, GUI_KO_ARGS);
        return;
    }
    server->frequency = frequency;
    ns_set_timeval_callback(
        server->net_server, 1000000 / server->frequency, &on_timeval);
    send_gui_sst(server, server->frequency);
}