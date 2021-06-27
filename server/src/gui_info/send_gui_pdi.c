/*
** EPITECH PROJECT, 2021
** SEND_GUI_PDI
** File description:
** Send_gui_pdi function
*/

#include "zappy_server.h"

void send_gui_pdi_to(zappy_client_t *gui, uint64_t player_id)
{
    zc_send(gui, "pdi %lu\n", player_id);
}

void send_gui_pdi(zappy_server_t *server, uint64_t player_id)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_pdi_to(gui, player_id);
    }
}