/*
** EPITECH PROJECT, 2021
** SEND_GUI_SST
** File description:
** Send_gui_sst function
*/

#include "zappy_server.h"

void send_gui_sst_to(zappy_client_t *gui, int frequency)
{
    zc_send(gui, "sst %d\n", frequency);
}

void send_gui_sst(zappy_server_t *server, int frequency)
{
    zappy_client_t *gui;

    LIST_ITERATE(it, server->net_server->clients)
    {
        gui = ((net_client_t *) it->data)->custom_data;
        if (gui && gui->type == CLIENT_GRAPHIC)
            send_gui_sst_to(gui, frequency);
    }
}