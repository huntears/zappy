/*
** EPITECH PROJECT, 2021
** NET_CLIENT
** File description:
** Net_client header
*/

#ifndef NET_CLIENT_H_
#define NET_CLIENT_H_

#include <netinet/ip.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#include "net_buffer.h"
#include "net_socket.h"

#define NEW_LINE "\n"

#define CLIENT_SEND_BUFF_SIZE (1024)

typedef struct net_server_s net_server_t;

typedef struct net_client_s net_client_t;
struct net_client_s {
    net_server_t *net_server;
    int socket;
    address_t addr;
    bool need_disconnection;
    bool disconnected;
    net_buffer_t write_buffer;
    void *custom_data;
    void *(*custom_destructor)(void *);
};

/// PROTOTYPES

// create / destroy
net_client_t *nc_create(net_server_t *net_server, int socket);
void *nc_destroy(net_client_t *net_client);

// send
int nc_send(net_client_t *net_client, const char *str, ...);
int nc_vsend(net_client_t *net_client, const char *str, va_list args);
int nc_send_line(net_client_t *net_client, const char *str);
int nc_send_raw(net_client_t *net_client, const void *raw_data, size_t len);

int nc_flush(net_client_t *net_client);

// recv
ssize_t nc_recv(net_client_t *net_client, char *buff, size_t buff_len);

#endif /* !NET_CLIENT_H_ */