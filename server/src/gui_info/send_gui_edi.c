/*
** EPITECH PROJECT, 2021
** SEND_GUI_EDI
** File description:
** Send_gui_edi function
*/

#include "zappy_server.h"

void send_gui_edi_to(zappy_client_t *gui, uint64_t egg_id)
{
    zc_send(gui, "edi %lu\n", egg_id);
}

void send_gui_edi(zappy_server_t *server, uint64_t egg_id)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_edi_to(gui, egg_id);
    }
}