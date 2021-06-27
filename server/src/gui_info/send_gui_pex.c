/*
** EPITECH PROJECT, 2021
** SEND_GUI_PEX
** File description:
** Send_gui_pex function
*/

#include "zappy_server.h"

void send_gui_pex_to(zappy_client_t *gui, uint64_t player_id)
{
    zc_send(gui, "pex %lu\n", player_id);
}

void send_gui_pex(zappy_server_t *server, uint64_t player_id)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_pex_to(gui, player_id);
    }
}