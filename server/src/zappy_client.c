/*
** EPITECH PROJECT, 2021
** ZAPPY_CLIENT
** File description:
** Zappy_client function
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "net/net_server.h"

#include "tools/tools.h"

#include "zappy_client.h"

zappy_client_t *zappy_client_create(net_client_t *net_client)
{
    zappy_client_t *zappy_client = malloc(sizeof(zappy_client_t));

    if (!zappy_client)
        return NULL;
    memset(zappy_client, 0, sizeof(zappy_client_t));
    zappy_client->net_client = net_client;
    return zappy_client;
}

void *zappy_client_destroy(zappy_client_t *zappy_client)
{
    if (!zappy_client)
        return NULL;
    if (zappy_client->ai)
        zappy_ai_destroy(zappy_client->ai);
    free(zappy_client);
    return NULL;
}

int zc_send(zappy_client_t *zappy_client, const char *str, ...)
{
    int return_value;
    va_list args;

    va_start(args, str);
    return_value = nc_vsend(zappy_client->net_client, str, args);
    va_end(args);
    return return_value;
}

int zc_send_line(zappy_client_t *zappy_client, const char *line)
{
    return nc_send_line(zappy_client->net_client, line);
}