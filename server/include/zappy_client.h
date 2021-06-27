/*
** EPITECH PROJECT, 2021
** ZAPPY_CLIENT
** File description:
** Zappy_client header
*/

#ifndef ZAPPY_CLIENT_H_
#define ZAPPY_CLIENT_H_

#include "net/net_client.h"

#include "zappy_ai.h"

enum client_type {
    CLIENT_UNKNOWN,
    CLIENT_AI,
    CLIENT_GRAPHIC,
};

typedef struct zappy_client {
    net_client_t *net_client;
    enum client_type type;
    zappy_ai_t *ai;
} zappy_client_t;

// create / destroy
zappy_client_t *zappy_client_create(net_client_t *net_client);
void *zappy_client_destroy(zappy_client_t *zappy_client);

void zappy_ai_die(zappy_client_t *zappy_client, zappy_server_t *server);

// send
int zc_send(zappy_client_t *zappy_client, const char *str, ...);
int zc_send_line(zappy_client_t *zappy_client, const char *line);

#endif /* !ZAPPY_CLIENT_H_ */