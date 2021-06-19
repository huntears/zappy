/*
** EPITECH PROJECT, 2021
** NET_CLIENT_SEND
** File description:
** Net_client_send function
*/

#include "private/gnu_source.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "net_server.h"

#include "net_client.h"

int nc_vsend(net_client_t *net_client, const char *str, va_list args)
{
    char *buff = NULL;
    int buff_len = vasprintf(&buff, str, args);
    int write_len;

    if (buff_len == -1) {
        if (buff)
            free(buff);
        return -1;
    }
    if (!buff)
        return -1;
    FD_SET(net_client->socket, &net_client->net_server->need_write_fds);
    write_len = net_buffer_push(&net_client->write_buffer, buff, buff_len);
    free(buff);
    return write_len;
}

int nc_send(net_client_t *net_client, const char *str, ...)
{
    int return_value;
    va_list args;

    va_start(args, str);
    return_value = nc_vsend(net_client, str, args);
    va_end(args);
    return return_value;
}

int nc_send_line(net_client_t *net_client, const char *str)
{
    return nc_send(net_client, "%s" NEW_LINE, str);
}

int nc_send_raw(net_client_t *net_client, const void *raw_data, size_t len)
{
    FD_SET(net_client->socket, &net_client->net_server->need_write_fds);
    return net_buffer_push(&net_client->write_buffer, raw_data, len);
}