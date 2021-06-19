/*
** EPITECH PROJECT, 2021
** NET_BUFFER
** File description:
** Net_buffer function
*/

#include <string.h>
#include <unistd.h>

#include "net_buffer.h"

bool net_buffer_push(net_buffer_t *buffer, const void *data, size_t len)
{
    if (!buffer->buffer) {
        buffer->length = 0;
        buffer->buffer = malloc(len);
        buffer->buffer_length = len;
    } else if (buffer->length + len > buffer->buffer_length) {
        buffer->buffer = realloc(buffer->buffer, buffer->length + len);
        buffer->buffer_length = buffer->length + len;
    }
    if (!buffer)
        return false;
    memmove(&buffer->buffer[buffer->length], data, len);
    buffer->length += len;
    return true;
}

void *net_buffer_pop(net_buffer_t *buffer, size_t len)
{
    char *data;

    if (!buffer->buffer || buffer->length == 0)
        return NULL;
    if (len > buffer->length)
        len = buffer->length;
    data = malloc(sizeof(char) * (len + 1));
    if (!data)
        return NULL;
    memcpy(data, buffer->buffer, len);
    data[len] = '\0';
    memmove(buffer->buffer, &buffer->buffer[len], buffer->length - len);
    buffer->length -= len;
    return data;
}

size_t net_buffer_copy(net_buffer_t *buffer, char *data, size_t len)
{
    if (!buffer->buffer || buffer->length == 0)
        return 0;
    if (len > buffer->length)
        len = buffer->length;
    memcpy(data, buffer->buffer, len);
    data[len] = '\0';
    return len;
}

void net_buffer_pop_in_nothing(net_buffer_t *buffer, size_t len)
{
    if (!buffer->buffer || buffer->length == 0)
        return;
    if (len >= buffer->length) {
        buffer->length = 0;
    } else {
        memmove(buffer->buffer, &buffer->buffer[len], buffer->length - len);
        buffer->length -= len;
    }
}

int net_buffer_flush(net_buffer_t *buffer, int fd)
{
    char buff[NET_BUFFER_FLUSH_SIZE + 1];
    size_t buff_len = net_buffer_copy(buffer, buff, NET_BUFFER_FLUSH_SIZE);
    int write_size;

    if (buff_len == 0)
        return 0;
    write_size = write(fd, buff, buff_len);
    if (write_size == -1)
        return -1;
    net_buffer_pop_in_nothing(buffer, write_size);
    return write_size;
}