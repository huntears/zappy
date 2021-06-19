/*
** EPITECH PROJECT, 2021
** SEND_GUI_PDR
** File description:
** Send_gui_pdr function: resource dropping
*/

#include "zappy_server.h"

void send_gui_pdr_to(zappy_client_t *gui, size_t player_number, int object_type)
{
    zc_send(gui, "pdr %zu %d\n", player_number, object_type);
}

void send_gui_pdr(zappy_server_t *server, size_t player_number, int object_type)
{
    zappy_client_t *gui;

    LIST_ITERATE(it, server->net_server->clients)
    {
        gui = ((net_client_t *) it->data)->custom_data;
        if (gui && gui->type == CLIENT_GRAPHIC)
            send_gui_pdr_to(gui, player_number, object_type);
    }
}