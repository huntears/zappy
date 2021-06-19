/*
** EPITECH PROJECT, 2021
** TEAM
** File description:
** Team function
*/

#include <string.h>

#include "tools.h"

#include "teams.h"

team_t *team_create(const char *name, size_t max_clients)
{
    team_t *team = malloc(sizeof(team_t));

    if (!team)
        return NULL;
    memset(team, 0, sizeof(team_t));
    team->max_ai = max_clients;
    team->name = strdup(name);
    team->eggs = list_create(&free);
    if (!team->name || !team->eggs)
        return team_destroy(team);
    return team;
}

team_t *team_destroy(team_t *team)
{
    if (!team)
        return NULL;
    if (team->name)
        free(team->name);
    if (team->eggs)
        list_destroy(team->eggs);
    free(team);
    return NULL;
}