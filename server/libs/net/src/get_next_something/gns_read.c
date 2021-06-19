/*
** EPITECH PROJECT, 2021
** BUFF_GNL
** File description:
** Buff_gnl function
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"

#include "net_buffer.h"

#include "gns/get_next_something.h"

int gns(int socket_fd)
{
    char buff[GNS_BUFF_SIZE + 1];
    gns_buffer_t *buffer = get_gns_buffer(socket_fd);
    int read_len;

    if (!buffer)
        return -1;
    read_len = read(socket_fd, buff, GNS_BUFF_SIZE);
    if (read_len > 0) {
        buff[read_len] = '\0';
        net_buffer_push(&buffer->buffer, buff, read_len);
    }
    return read_len;
}