/*
** EPITECH PROJECT, 2021
** NET_SERVER_RUN
** File description:
** Net_server_run function
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "list.h"

#include "interval.h"

#include "net_server.h"
#include "net_socket.h"

static void ns_accept_new_client(net_server_t *net_server, int socket_fd)
{
    int new_socket;
    socklen_t addr_len = sizeof(sockaddr_t);
    sockaddr_t addr;
    net_client_t *client = NULL;

    new_socket = accept(socket_fd, (struct sockaddr *) &addr, &addr_len);
    if (new_socket == -1) {
        perror("Accept failed");
        return;
    }
    client = nc_create(net_server, new_socket);
    if (!client) {
        fprintf(stderr, "Can not create net_client: memory exhausted\n");
        close_socket(new_socket);
        return;
    }
    ns_add_client(net_server, client);
    FD_SET(new_socket, &net_server->need_read_fds);
    extend_interval(&net_server->socket_interval, new_socket);
    NS_CALLBACK(net_server, on_accept, client);
}

static void ns_run_ready_socket(net_server_t *net_server, int socket_fd)
{
    net_client_t *client = NULL;

    if (socket_fd == net_server->socket)
        ns_accept_new_client(net_server, socket_fd);
    else {
        client = ns_get_client(net_server, socket_fd);
        NS_CALLBACK(net_server, on_ready, client);
    }
}

static void process_fds(
    net_server_t *net_server, fd_set *read_fds, fd_set *write_fds)
{
    net_client_t *net_client = NULL;

    FOREACH_SOCKET(fd, net_server->socket_interval, write_fds) {
        net_client = ns_get_client(net_server, fd);
        if (net_client->need_disconnection)
            ns_disconnect_client(net_server, net_client);
        if (net_client->disconnected && net_client->write_buffer.length == 0) {
            ns_remove_client(net_server, net_client);
            continue;
        }
        if (nc_flush(net_client) == -1)
            ns_remove_client(net_server, net_client);
        else if (net_client->disconnected
            && net_client->write_buffer.length == 0)
            ns_remove_client(net_server, net_client);
    }
    FOREACH_SOCKET(fd, net_server->socket_interval, read_fds) {
        ns_run_ready_socket(net_server, fd);
    }
}

static void process_timeval(net_server_t *ns, struct timespec *start)
{
    struct timespec stop;
    time_t elapsed_ms;
    time_t elapsed_ms_stop;

    clock_gettime(4, &stop);
    elapsed_ms = (stop.tv_nsec - start->tv_nsec) / 1000
        + (stop.tv_sec - start->tv_sec) * 1000000;
    if ((ns->current_timeval.tv_sec == 0 && ns->current_timeval.tv_usec == 0)
        || ns->current_timeval.tv_usec <= elapsed_ms) {
        ns->on_timeval(ns);
        elapsed_ms_stop = elapsed_ms - ns->current_timeval.tv_usec;
        memcpy(&ns->current_timeval, &ns->timeval, sizeof(struct timeval));
        if (ns->current_timeval.tv_usec > elapsed_ms_stop)
            ns->current_timeval.tv_usec -= elapsed_ms_stop;
        else
            ns->current_timeval.tv_usec = 0;
    } else {
        ns->current_timeval.tv_usec -= elapsed_ms;
    }
}

void ns_run(net_server_t *ns)
{
    struct timespec start;

    ns->running = true;
    printf("Run server on port: %d\n", ntohs(ns->addr.sa_in.sin_port));
    clock_gettime(4, &start);
    while (ns->running) {
        if (ns->on_timeval)
            process_timeval(ns, &start);
        if (select(FD_SETSIZE, &ns->read_fds, &ns->write_fds, NULL,
                ns->on_timeval ? &ns->current_timeval : NULL)
            == -1) {
            printf("Select failed: %s\n", strerror(errno));
            break;
        }
        clock_gettime(4, &start);
        process_fds(ns, &ns->read_fds, &ns->write_fds);
        memcpy(&ns->read_fds, &ns->need_read_fds, sizeof(fd_set));
        memcpy(&ns->write_fds, &ns->need_write_fds, sizeof(fd_set));
    }
    ns_close_all_sockets(ns);
}