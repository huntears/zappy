/*
** EPITECH PROJECT, 2021
** NET_CLIENT_RECV
** File description:
** Net_client_recv function
*/

#include <unistd.h>

#include "net_client.h"

ssize_t nc_recv(net_client_t *net_client, char *buff, size_t buff_len)
{
    ssize_t read_len = read(net_client->socket, buff, buff_len);

    if (read_len == -1)
        return read_len;
    buff[read_len] = '\0';
    return read_len;
}