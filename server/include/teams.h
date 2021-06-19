/*
** EPITECH PROJECT, 2021
** TEAMS
** File description:
** Teams header
*/
#ifndef TEAM_H_
#define TEAM_H_

#include <stdlib.h>

#include "list/list.h"

#include "egg.h"

typedef struct team {
    char *name;
    list_t *eggs;
    size_t max_ai;
    size_t nb_ai;
    size_t levels[8];
} team_t;

// team create / destroy
team_t *team_create(const char *name, size_t max_clients);
team_t *team_destroy(team_t *team);

int team_get_connect_nbr(team_t *team);
bool team_can_ai_spawn(team_t *team);
void team_spawn_ai(team_t *team, int *x, int *y);

bool team_add_egg(team_t *team, int x, int y);

// teams create / destroy
team_t **teams_create(list_t *team_names, size_t max_clients);
void *teams_destroy(team_t **teams);

#endif /* !TEAM_H_ */