/*
** EPITECH PROJECT, 2021
** TEAM_SPAWN
** File description:
** Team_spawn function
*/

#include "tools.h"

#include "teams.h"

int team_get_connect_nbr(team_t *team)
{
    return MAX((int) team->max_ai - (int) team->nb_ai, team->eggs->size);
}

bool team_can_ai_spawn(team_t *team)
{
    return team_get_connect_nbr(team) > 0;
}

void team_spawn_ai(team_t *team, int *x, int *y)
{
}