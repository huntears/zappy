/*
** EPITECH PROJECT, 2021
** CMD_GUI
** File description:
** CMD_gui function
*/

#include <string.h>

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

const struct server_gui_cmd server_gui_cmds[] = {
    { "msz", false, CMD_PROT(gui_msz) },
    { "bct", true, CMD_PROT(gui_bct) },
    { "mct", false, CMD_PROT(gui_mct) },
    { "tna", false, CMD_PROT(gui_tna) },
    { "ppo", true, CMD_PROT(gui_ppo) },
    { "plv", true, CMD_PROT(gui_plv) },
    { "pin", true, CMD_PROT(gui_pin) },
    { "sgt", false, CMD_PROT(gui_sgt) },
    { "sst", true, CMD_PROT(gui_sst) },
    { "", false, NULL },
};

void cmd_gui(zappy_server_t *server, zappy_client_t *client, const char *line)
{
    size_t cmd_len;

    for (size_t k = 0; server_gui_cmds[k].cmd; k++) {
        cmd_len = strlen(server_gui_cmds[k].key);
        if (strncmp(server_gui_cmds[k].key, line, cmd_len))
            continue;
        if ((server_gui_cmds[k].required_arguments && line[cmd_len] != ' ')
            || (!server_gui_cmds[k].required_arguments
                && line[cmd_len] != '\0')) {
            zc_send_line(client, GUI_KO_ARGS);
            return;
        }
        server_gui_cmds[k].cmd(server, client, line);
        return;
    }
    zc_send_line(client, GUI_KO);
}