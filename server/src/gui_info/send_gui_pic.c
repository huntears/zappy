/*
** EPITECH PROJECT, 2021
** SEND_GUI_PIC
** File description:
** Send_gui_pic function
*/

#include "zappy_server.h"

void send_gui_pic_to(
    zappy_client_t *gui, zappy_client_t *client, zappy_server_t *server)
{
    zc_send(gui, "pic %d %d %lu %lu", client->ai->x, client->ai->y,
        client->ai->level + 1, client->ai->id);
    ITERATE_AIS(ai, server)
    {
        if (ai->ai->x != client->ai->x || ai->ai->y != client->ai->y)
            continue;
        if (ai->ai->id == client->ai->id)
            continue;
        zc_send(gui, " %lu", ai->ai->id);
    }
    zc_send(gui, "\n");
}

void send_gui_pic(zappy_server_t *server, zappy_client_t *client)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_pic_to(gui, client, server);
    }
}