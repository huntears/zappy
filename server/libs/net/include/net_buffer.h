/*
** EPITECH PROJECT, 2021
** NET_BUFFER
** File description:
** Net_buffer header
*/

#ifndef NET_BUFFER_H_
#define NET_BUFFER_H_

#include <stdbool.h>
#include <stdlib.h>

#define NET_BUFFER_FLUSH_SIZE (1024)

typedef struct net_buffer_s net_buffer_t;
struct net_buffer_s {
    char *buffer;
    size_t length;
    size_t buffer_length;
};

bool net_buffer_push(net_buffer_t *buffer, const void *data, size_t len);
void *net_buffer_pop(net_buffer_t *buffer, size_t len);

size_t net_buffer_copy(net_buffer_t *buffer, char *data, size_t len);
void net_buffer_pop_in_nothing(net_buffer_t *buffer, size_t len);

int net_buffer_flush(net_buffer_t *buffer, int fd);

#endif /* !NET_BUFFER_H_ */