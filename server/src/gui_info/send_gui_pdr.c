/*
** EPITECH PROJECT, 2021
** SEND_GUI_PDR
** File description:
** Send_gui_pdr function: resource dropping
*/

#include "zappy_server.h"

void send_gui_pdr_to(zappy_client_t *gui, uint64_t player_id, int object_type)
{
    zc_send(gui, "pdr %lu %d\n", player_id, object_type);
}

void send_gui_pdr(zappy_server_t *server, uint64_t player_id, int object_type)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_pdr_to(gui, player_id, object_type);
    }
}