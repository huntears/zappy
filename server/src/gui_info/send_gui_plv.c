/*
** EPITECH PROJECT, 2021
** SEND_GUI_PLV
** File description:
** Send_gui_plv function
*/

#include "zappy_server.h"

void send_gui_plv_to(zappy_client_t *gui, zappy_client_t *client)
{
    zc_send(gui, "plv %lu %lu\n", client->ai->id, client->ai->level + 1);
}

void send_gui_plv(zappy_server_t *server, zappy_client_t *client)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_plv_to(gui, client);
    }
}