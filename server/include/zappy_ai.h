/*
** EPITECH PROJECT, 2021
** ZAPPY_AI
** File description:
** Zappy_ai header
*/

#ifndef ZAPPY_AI_H_
#define ZAPPY_AI_H_

#include <stdbool.h>

#include "list/list.h"

#include "object.h"
#include "teams.h"

#define REMAINING_TIME_PER_FOOD (126)

typedef struct zappy_server zappy_server_t;
typedef struct zappy_client zappy_client_t;

enum direction {
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

typedef struct zappy_ai {
    size_t id;
    team_t *team_endpoint;
    list_t *commands_queue;
    bool is_alive;
    size_t level;
    int x;
    int y;
    enum direction direction;
    size_t remaining_time;
    size_t inventory[NB_OBJECTS];
    bool is_fork;
    bool is_incantated;
    bool pre_incantation_success;
} zappy_ai_t;

struct incant_requirements {
    size_t nb_of_players;
    size_t objects[NB_OBJECTS - 1];
};

// create / destroy
zappy_ai_t *zappy_ai_create(zappy_server_t *server, team_t *team_endpoint);
void *zappy_ai_destroy(zappy_ai_t *zappy_ai);

bool zappy_ai_consume_time(
    zappy_server_t *server, zappy_client_t *client, size_t consume_time);

#endif /* !ZAPPY_AI_H_ */