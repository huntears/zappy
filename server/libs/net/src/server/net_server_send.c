/*
** EPITECH PROJECT, 2021
** NET_SERVER_SEND
** File description:
** Net_server_send function
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"
#include "net_server.h"

int ns_send(net_server_t *net_server, const char *str, ...)
{
    int return_value;
    va_list args;

    va_start(args, str);
    return_value = ns_vsend(net_server, str, args);
    va_end(args);
    return return_value;
}

int ns_vsend(net_server_t *net_server, const char *str, va_list args)
{
    int return_value = 0;
    net_client_t *net_client;
    va_list tmp_args;

    for (list_it_t *it = list_get_it(net_server->clients); it; next_it(&it)) {
        net_client = it->data;
        va_copy(tmp_args, args);
        return_value += nc_vsend(net_client, str, tmp_args);
        va_end(tmp_args);
    }
    return return_value;
}

int ns_send_line(net_server_t *net_server, const char *str)
{
    return ns_send(net_server, "%s%s", str, NEW_LINE);
}

int ns_send_raw(net_server_t *net_server, const char *raw_data, size_t len)
{
    int return_value = 0;
    net_client_t *net_client;

    for (list_it_t *it = list_get_it(net_server->clients); it; next_it(&it)) {
        net_client = it->data;
        return_value += nc_send_raw(net_client, raw_data, len);
    }
    return return_value;
}