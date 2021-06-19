/*
** EPITECH PROJECT, 2021
** GET_NEXT_SOMETHING
** File description:
** Get_next_something header
*/

#ifndef GET_NEXT_SOMETHING_H_
#define GET_NEXT_SOMETHING_H_

#include "net_buffer.h"

#ifndef GNS_BUFF_SIZE
#define GNS_BUFF_SIZE (1024)
#endif /* !GNS_BUFF_SIZE */

typedef struct list_s list_t;

typedef struct gns_buffer_s gns_buffer_t;
struct gns_buffer_s
{
    int socket_fd;
    net_buffer_t buffer;
};

list_t *gns_fd_list_handler(int action);

int gns(int socket_fd);

void gns_clear_socket(int socket_fd);
void gns_clear_sockets(void);

gns_buffer_t *get_gns_buffer(int socket_fd);

#endif /* !GET_NEXT_SOMETHING_H_ */