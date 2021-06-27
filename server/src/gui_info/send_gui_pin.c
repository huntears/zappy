/*
** EPITECH PROJECT, 2021
** SEND_GUI_PIN
** File description:
** Send_gui_pin function
*/

#include "zappy_server.h"

void send_gui_pin_to(zappy_client_t *gui, zappy_client_t *client)
{
    size_t *inventory = client->ai->inventory;

    zc_send(gui, "pin %lu %d %d %lu %lu %lu %lu %lu %lu %lu\n", client->ai->id,
        client->ai->x, client->ai->y, inventory[0], inventory[1], inventory[2],
        inventory[3], inventory[4], inventory[5], inventory[6]);
}

void send_gui_pin(zappy_server_t *server, zappy_client_t *client)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_pin_to(gui, client);
    }
}