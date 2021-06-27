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

typedef struct zappy_client zappy_client_t;
typedef struct zappy_server zappy_server_t;

typedef struct team {
    char *name;
    size_t max_ai;
    size_t nb_ai;
    size_t levels[8];
    list_t *hatching_eggs;
    list_t *hatched_eggs;
} team_t;

// team create / destroy
team_t *team_create(const char *name, size_t max_clients);
team_t *team_destroy(team_t *team);

int team_get_connect_nbr(team_t *team);
bool team_can_ai_spawn(team_t *team);
void team_spawn_ai(team_t *team, zappy_server_t *server, int *x, int *y);

bool team_add_egg(team_t *team, zappy_client_t *client, zappy_server_t *server);
void team_consume_time(
    zappy_server_t *server, team_t *team, size_t consume_time);

// teams create / destroy
team_t **teams_create(list_t *team_names, size_t max_clients);
void *teams_destroy(team_t **teams);

#endif /* !TEAM_H_ */