/*
** EPITECH PROJECT, 2021
** GNS_CLEAR
** File description:
** Gns_clear function
*/

#include <stdlib.h>

#include "list.h"

#include "gns/get_next_something.h"

void gns_clear_socket(int socket_fd)
{
    list_t *fd_list = gns_fd_list_handler(0);
    gns_buffer_t *gns_buff = NULL;

    for (int k = 0; k < fd_list->size; k++) {
        gns_buff = (gns_buffer_t *) list_get(fd_list, k);
        if (gns_buff->socket_fd == socket_fd) {
            list_remove(fd_list, k);
            return;
        }
    }
}

void gns_clear_sockets(void)
{
    gns_fd_list_handler(2);
    gns_fd_list_handler(1);
}