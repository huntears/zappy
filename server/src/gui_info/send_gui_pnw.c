/*
** EPITECH PROJECT, 2021
** SEND_GUI_PNW
** File description:
** Send_gui_pnw function
*/

#include "zappy_server.h"

void send_gui_pnw_to(zappy_client_t *gui, zappy_client_t *client)
{
    zc_send(gui, "pnw %lu %d %d %d %lu %s\n", client->ai->id, client->ai->x,
        client->ai->y, client->ai->direction + 1, client->ai->level + 1,
        client->ai->team_endpoint->name);
}

void send_gui_pnw(zappy_server_t *server, zappy_client_t *client)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_pnw_to(gui, client);
    }
}