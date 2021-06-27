/*
** EPITECH PROJECT, 2021
** SEND_GUI_EBO
** File description:
** Send_gui_ebo function
*/

#include "zappy_server.h"

void send_gui_ebo_to(zappy_client_t *gui, uint64_t egg_id)
{
    zc_send(gui, "ebo %lu\n", egg_id);
}

void send_gui_ebo(zappy_server_t *server, uint64_t egg_id)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_ebo_to(gui, egg_id);
    }
}