/*
** EPITECH PROJECT, 2021
** TEAMS
** File description:
** Teams function
*/

#include "list/list.h"

#include "teams.h"

team_t **teams_create(list_t *team_names, size_t max_clients)
{
    team_t **teams = malloc(sizeof(team_t *) * (team_names->size + 1));

    if (!teams)
        return NULL;
    LIST_ITERATE_N(it, team_names, id)
    {
        teams[id] = team_create(it->data, max_clients);
        if (!teams[id])
            return teams_destroy(teams);
    }
    teams[team_names->size] = NULL;
    return teams;
}

void *teams_destroy(team_t **teams)
{
    if (!teams)
        return NULL;
    for (size_t team_id = 0; teams[team_id]; team_id++)
        team_destroy(teams[team_id]);
    free(teams);
    return NULL;
}