/*
** EPITECH PROJECT, 2021
** TEAM
** File description:
** Team function
*/

#include <string.h>

#include "tools/tools.h"

#include "server_cmds.h"
#include "teams.h"

static void egg_destroy_no_rtn(egg_t *egg)
{
    egg_destroy(egg);
}

team_t *team_create(const char *name, size_t max_clients)
{
    team_t *team = malloc(sizeof(team_t));

    if (!team)
        return NULL;
    memset(team, 0, sizeof(team_t));
    team->max_ai = max_clients;
    team->name = strdup(name);
    team->hatching_eggs = list_create((void (*)(void *)) egg_destroy_no_rtn);
    team->hatched_eggs = list_create((void (*)(void *)) egg_destroy_no_rtn);
    if (!team->name || !team->hatching_eggs || !team->hatched_eggs)
        return team_destroy(team);
    return team;
}

team_t *team_destroy(team_t *team)
{
    if (!team)
        return NULL;
    if (team->name)
        free(team->name);
    if (team->hatching_eggs)
        list_destroy(team->hatching_eggs);
    if (team->hatched_eggs)
        list_destroy(team->hatched_eggs);
    free(team);
    return NULL;
}

void remove_hatched_eggs(zappy_server_t *server, team_t *team)
{
    egg_t *egg;

    LIST_ITERATE_N(hatching_egg_it, team->hatching_eggs, id)
    {
        egg = hatching_egg_it->data;
        if (egg->time_to_hatching == 0) {
            send_gui_eht(server, egg->id);
            list_pop(team->hatching_eggs, id);
            list_add(team->hatched_eggs, egg);
            remove_hatched_eggs(server, team);
            return;
        }
    }
}

void team_consume_time(
    zappy_server_t *server, team_t *team, size_t consume_time)
{
    egg_t *egg;

    LIST_ITERATE(hatching_egg_it, team->hatching_eggs)
    {
        egg = hatching_egg_it->data;
        if (egg->time_to_hatching <= consume_time)
            egg->time_to_hatching = 0;
        else
            egg->time_to_hatching -= consume_time;
    }
    remove_hatched_eggs(server, team);
}