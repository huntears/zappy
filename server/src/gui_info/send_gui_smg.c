/*
** EPITECH PROJECT, 2021
** SEND_GUI_SMG
** File description:
** Send_gui_smg function
*/

#include "zappy_server.h"

void send_gui_smg_to(zappy_client_t *gui, const char *server_msg)
{
    zc_send(gui, "smg %s\n", server_msg);
}

void send_gui_smg(zappy_server_t *server, const char *server_msg)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_smg_to(gui, server_msg);
    }
}