/*
** EPITECH PROJECT, 2021
** GET_NEXT_LINE
** File description:
** Get_next_line function
*/

#include <stdlib.h>
#include <string.h>

#include "gns/get_next_line.h"
#include "gns/get_next_something.h"

static int get_new_line_pos(net_buffer_t *buffer)
{
    for (size_t k = 0; k < buffer->length; k++)
        if (buffer->buffer[k] == '\n')
            return k;
    return -1;
}

static char *remove_carriage(char *line)
{
    if (!line)
        return NULL;
    if (strlen(line) > 0 && line[strlen(line) - 1] == '\r')
        line[strlen(line) - 1] = '\0';
    return line;
}

static char *try_to_extract_line(net_buffer_t *buffer)
{
    char *line = NULL;
    int new_line_pos;

    if (!buffer)
        return NULL;
    new_line_pos = get_new_line_pos(buffer);
    if (new_line_pos == -1)
        return NULL;
    line = net_buffer_pop(buffer, new_line_pos + 1);
    if (!line)
        return NULL;
    line[new_line_pos] = '\0';
    return remove_carriage(line);
}

char *gnl_extract_next_line(int socket_fd)
{
    gns_buffer_t *buffer = get_gns_buffer(socket_fd);

    if (!buffer)
        return NULL;
    return try_to_extract_line(&buffer->buffer);
}

char *gnl(int socket_fd, int *read_len)
{
    gns_buffer_t *buffer = get_gns_buffer(socket_fd);
    char *line;

    if (!buffer) {
        *read_len = -1;
        return NULL;
    }
    line = try_to_extract_line(&buffer->buffer);
    if (line) {
        *read_len = strlen(line);
        return line;
    }
    *read_len = gns(socket_fd);
    if (*read_len <= 0)
        return NULL;
    return try_to_extract_line(&buffer->buffer);
}