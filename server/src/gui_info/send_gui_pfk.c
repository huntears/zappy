/*
** EPITECH PROJECT, 2021
** SEND_GUI_PFK
** File description:
** Send_gui_pfk function
*/

#include "zappy_server.h"

void send_gui_pfk_to(zappy_client_t *gui, uint64_t player_id)
{
    zc_send(gui, "pfk %lu\n", player_id);
}

void send_gui_pfk(zappy_server_t *server, uint64_t player_id)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_pfk_to(gui, player_id);
    }
}