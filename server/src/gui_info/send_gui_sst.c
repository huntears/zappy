/*
** EPITECH PROJECT, 2021
** SEND_GUI_SST
** File description:
** Send_gui_sst function
*/

#include "zappy_server.h"

void send_gui_sst_to(zappy_client_t *gui, uint64_t frequency)
{
    zc_send(gui, "sst %lu\n", frequency);
}

void send_gui_sst(zappy_server_t *server, uint64_t frequency)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_sst_to(gui, frequency);
    }
}