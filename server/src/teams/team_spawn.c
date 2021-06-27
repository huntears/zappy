/*
** EPITECH PROJECT, 2021
** TEAM_SPAWN
** File description:
** Team_spawn function
*/

#include "tools/tools.h"

#include "server_cmds.h"
#include "teams.h"

int team_get_connect_nbr(team_t *team)
{
    return MAX(
        (int) team->max_ai - (int) team->nb_ai, (int) team->hatched_eggs->size);
}

bool team_can_ai_spawn(team_t *team)
{
    return team_get_connect_nbr(team) > 0;
}

void team_spawn_ai(team_t *team, zappy_server_t *server, int *x, int *y)
{
    egg_t *egg;

    if (team->hatched_eggs->size <= 0)
        return;
    egg = list_get(team->hatched_eggs, 0);
    map_get_chunk(server->map, *x, *y)->nb_players--;
    *x = egg->x;
    *y = egg->y;
    map_get_chunk(server->map, *x, *y)->nb_players++;
    send_gui_ebo(server, egg->id);
    list_remove(team->hatched_eggs, 0);
}