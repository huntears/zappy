/*
** EPITECH PROJECT, 2021
** SEND_GUI_SEG
** File description:
** Send_gui_seg function
*/

#include "zappy_server.h"

void send_gui_seg_to(zappy_client_t *gui, const char *winning_team_name)
{
    zc_send(gui, "seg %s\n", winning_team_name);
}

void send_gui_seg(zappy_server_t *server, const char *winning_team_name)
{
    ITERATE_GUIS(gui, server)
    {
        send_gui_seg_to(gui, winning_team_name);
    }
}