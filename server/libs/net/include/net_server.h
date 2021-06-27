/*
** EPITECH PROJECT, 2021
** NET_SERVER
** File description:
** Net_server header
*/

#ifndef NET_SERVER_H_
#define NET_SERVER_H_

#include <netinet/ip.h>
#include <sys/select.h>
#include <stdbool.h>
#include <stdarg.h>

#include "interval.h"
#include "net_client.h"
#include "net_socket.h"

#ifndef EOT
#define EOT (4)
#endif /* EOT */

// macro
#define NS_CALLBACK(server, callback, client)           \
    ns_process_callback(                                \
        server, client,                                 \
        (server->callbacks.callback) ?                  \
        (server->callbacks.callback)(server, client) :  \
        NS_NOTHING                                      \
    )
#define NS_CMD_AV(server, callback, client, ...)               \
    ns_process_callback(                                            \
        server, client,                                             \
        (server->callbacks.callback) ?                              \
        (server->callbacks.callback)(server, client, __VA_ARGS__) : \
        NS_NOTHING                                                  \
    )
#define FOREACH_SOCKET(var, interval, readfds) \
    FOR_INTERVAL(var, interval) if (FD_ISSET(var, readfds))
#define FOREACH_REV_SOCKET(var, interval, readfds) \
    FOR_REV_INTERVAL(var, interval) if (FD_ISSET(var, readfds))

// enum
typedef enum ns_status
{
    NS_NOTHING,
    NS_OK,
    NS_DISCONNECT_CLIENT,
    NS_CLOSE_CLIENT,
    NS_CLOSE_SERVER,
} ns_status_e;

// typedef
typedef struct net_server_s net_server_t;
typedef struct ns_callbacks_s ns_callbacks_t;
typedef struct list_s list_t;

// struct
struct ns_callbacks_s
{
    ns_status_e (*on_accept)(net_server_t *server, net_client_t *client);
    ns_status_e (*on_ready)(net_server_t *server, net_client_t *client);
    ns_status_e (*on_disconnect)(net_server_t *server, net_client_t *client);
    void (*on_close)(net_server_t *server, net_client_t *client);
};

struct net_server_s
{
    bool running;
    int socket;
    address_t addr;
    list_t *clients;
    interval_t socket_interval;
    ns_callbacks_t callbacks;
    fd_set need_read_fds;
    fd_set need_write_fds;
    fd_set read_fds;
    fd_set write_fds;
    struct timeval timeval;
    struct timeval current_timeval;
    void (*on_timeval)(net_server_t *);
    void *custom_data;
    void *(*custom_destructor)(void *);
};

/// PROTOTYPES

// create / destroy
net_server_t *ns_create(sa_family_t domain, int type, uint16_t port);
void *ns_destroy(net_server_t *net_server);

// run
bool ns_accept_one(net_server_t *net_server);
void ns_run(net_server_t *net_server);
void ns_close_all_sockets(net_server_t *net_server);

// callbacks
void ns_process_callback(net_server_t *net_server, net_client_t *net_client,
    ns_status_e status);

void ns_set_callbacks(net_server_t *net_server, ns_callbacks_t callbacks);
ns_callbacks_t *ns_get_callbacks(net_server_t *net_server);

void ns_set_timeval_callback(
    net_server_t *net_server, uint64_t ms, void (*on_timeval)(net_server_t *));

// process
void ns_disconnect_fd_client(net_server_t *net_server, int socket_fd);
void ns_disconnect_client(net_server_t *net_server, net_client_t *net_client);

// clients
bool ns_add_client(net_server_t *ns, net_client_t *net_client);
void ns_remove_client(net_server_t *net_server, net_client_t *net_client);
net_client_t *ns_get_client(net_server_t *net_server, int socket_fd);

// send
int ns_send(net_server_t *net_server, const char *str, ...);
int ns_vsend(net_server_t *net_server, const char *str, va_list args);
int ns_send_line(net_server_t *net_server, const char *str);
int ns_send_raw(net_server_t *net_server, const char *raw_data, size_t len);

#endif /* !NET_SERVER_H_ */