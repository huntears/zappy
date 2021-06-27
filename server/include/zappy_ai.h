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

struct zappy_ai_cmd {
    list_t *commands_queue;
    int time_before_cmd_execution;
};

typedef struct zappy_ai {
    uint64_t id;
    team_t *team_endpoint;
    struct zappy_ai_cmd commands;
    bool is_alive;
    uint64_t level;
    int x;
    int y;
    enum direction direction;
    uint64_t remaining_time;
    uint64_t inventory[NB_OBJECTS];
    bool is_fork;
    bool is_incantated;
    bool pre_incantation_success;
} zappy_ai_t;

struct incant_requirements {
    uint64_t nb_of_players;
    uint64_t objects[NB_OBJECTS - 1];
};

// create / destroy
zappy_ai_t *zappy_ai_create(
    zappy_server_t *server, team_t *team_endpoint, size_t id);
void *zappy_ai_destroy(zappy_ai_t *zappy_ai);

void store_cmd_ai(zappy_client_t *client, const char *line);
bool zappy_ai_consume_time(
    zappy_server_t *server, zappy_client_t *client, size_t consume_time);

#endif /* !ZAPPY_AI_H_ */