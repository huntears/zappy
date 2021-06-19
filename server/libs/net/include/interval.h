/*
** EPITECH PROJECT, 2021
** INTERVAL
** File description:
** Interval header
*/

#ifndef INTERVAL_H_
#define INTERVAL_H_

#include <stdbool.h>

typedef struct interval_s interval_t;
struct interval_s
{
    int from;
    int to;
    bool to_included;
};

#define FOR_INTERVAL(var, interval) for (         \
    int var = (interval).from;                      \
    var < (interval).to + (interval).to_included; \
    var++)

#define FOR_REV_INTERVAL(var, interval) for (       \
    int var = (interval).to;                        \
    var > (interval).from - (interval).to_included; \
    var--)

/// PROTOTYPES

void extend_interval(interval_t *interval, int value);

void remove_fd_socket_from_interval(
    interval_t *interval, fd_set *fds, int socket_fd);

#endif /* !INTERVAL_H_ */