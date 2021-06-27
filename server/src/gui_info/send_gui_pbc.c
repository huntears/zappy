/*
** EPITECH PROJECT, 2021
** SEND_GUI_PBC
** File description:
** Send_gui_pbc function
*/

#include "zappy_server.h"

void send_gui_pbc_to(zappy_client_t *gui, uint64_t player_id, const char *msg)
{
    zc_send(gui, "pbc %lu %s\n", player_id, msg);
}

void send_gui_pbc(zappy_server_t *server, uint64_t player_id, const char *msg)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_pbc_to(gui, player_id, msg);
    }
}