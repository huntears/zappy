/*
** EPITECH PROJECT, 2021
** TEAM_EGG
** File description:
** Team_egg function
*/

#include "egg.h"
#include "server_cmds.h"
#include "teams.h"
#include "zappy_server.h"

bool team_add_egg(team_t *team, zappy_client_t *client, zappy_server_t *server)
{
    egg_t *egg = egg_create(client->ai->id, client->ai->x, client->ai->y);

    if (!egg)
        return false;
    send_gui_enw(server, egg);
    list_add(team->hatching_eggs, egg);
    return true;
}