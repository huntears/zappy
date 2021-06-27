/*
** EPITECH PROJECT, 2021
** SEND_GUI_PIE
** File description:
** Send_gui_pie function
*/

#include "zappy_server.h"

void send_gui_pie_to(zappy_client_t *gui, int x, int y, bool result)
{
    zc_send(gui, "pie %d %d %d\n", x, y, !!result);
}

void send_gui_pie(zappy_server_t *server, int x, int y, bool result)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_pie_to(gui, x, y, result);
    }
}