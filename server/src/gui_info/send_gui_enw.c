/*
** EPITECH PROJECT, 2021
** SEND_GUI_ENW
** File description:
** Send_gui_enw function
*/

#include "zappy_server.h"

void send_gui_enw_to(zappy_client_t *gui, egg_t *egg)
{
    zc_send(
        gui, "enw %lu %lu %d %d\n", egg->id, egg->player_id, egg->x, egg->y);
}

void send_gui_enw(zappy_server_t *server, egg_t *egg)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_enw_to(gui, egg);
    }
}