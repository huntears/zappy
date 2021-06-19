/*
** EPITECH PROJECT, 2021
** INTERVAL
** File description:
** Interval function
*/

#include "net_server.h"

#include "interval.h"

void extend_interval(interval_t *interval, int value)
{
    if (value > interval->to)
        interval->to = value;
    if (value < interval->from)
        interval->from = value;
}

void remove_fd_socket_from_interval(
    interval_t *interval, fd_set *fds, int socket_fd)
{
    if (socket_fd == interval->from) {
        FOREACH_SOCKET(fd, *interval, fds)
        {
            interval->from = fd;
            break;
        }
    }
    if (socket_fd == interval->to) {
        FOREACH_REV_SOCKET(fd, *interval, fds)
        {
            interval->to = fd;
            break;
        }
    }
}