/*
** EPITECH PROJECT, 2021
** SEND_GUI_PPO
** File description:
** Send_gui_ppo function
*/

#include "zappy_server.h"

void send_gui_ppo_to(zappy_client_t *gui, zappy_client_t *client)
{
    zc_send(gui, "ppo %lu %d %d %d\n", client->ai->id, client->ai->x,
        client->ai->y, client->ai->direction + 1);
}

void send_gui_ppo(zappy_server_t *server, zappy_client_t *client)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_ppo_to(gui, client);
    }
}