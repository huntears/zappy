/*
** EPITECH PROJECT, 2021
** SEND_GUI_EHT
** File description:
** Send_gui_eht function
*/

#include "zappy_server.h"

void send_gui_eht_to(zappy_client_t *gui, uint64_t egg_id)
{
    zc_send(gui, "eht %lu\n", egg_id);
}

void send_gui_eht(zappy_server_t *server, uint64_t egg_id)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_eht_to(gui, egg_id);
    }
}