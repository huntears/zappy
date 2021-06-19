/*
** EPITECH PROJECT, 2021
** GNS_FD_LIST
** File description:
** Gns_fd_list function
*/

#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "list.h"

#include "gns/get_next_something.h"

static void gns_buff_destroy(gns_buffer_t *gnl_buff)
{
    if (!gnl_buff)
        return;
    if (gnl_buff->buffer.buffer)
        free(gnl_buff->buffer.buffer);
    free(gnl_buff);
}

static void __attribute__((constructor)) init_gnl(void)
{
    gns_fd_list_handler(1);
}

static void __attribute__((destructor)) destroy_gnl(void)
{
    gns_fd_list_handler(2);
}

list_t *gns_fd_list_handler(int action)
{
    static list_t *fd_list = NULL;

    if (action == 1)
        fd_list = list_create((void (*)(void *)) gns_buff_destroy);
    else if (action == 2) {
        list_destroy(fd_list);
        fd_list = NULL;
    }
    return fd_list;
}

gns_buffer_t *get_gns_buffer(int socket_fd)
{
    list_t *fd_list = gns_fd_list_handler(0);
    gns_buffer_t *gnl_buff = NULL;

    for (int k = 0; k < fd_list->size; k++) {
        gnl_buff = (gns_buffer_t *) list_get(fd_list, k);
        if (gnl_buff->socket_fd == socket_fd)
            return gnl_buff;
    }
    gnl_buff = malloc(sizeof(gns_buffer_t));
    if (!gnl_buff)
        return NULL;
    gnl_buff->socket_fd = socket_fd;
    memset(&gnl_buff->buffer, 0, sizeof(net_buffer_t));
    list_add(fd_list, gnl_buff);
    return gnl_buff;
}