/*
** EPITECH PROJECT, 2021
** NET_SERVER_CMDS
** File description:
** Net_server_cmds function
*/

#include <string.h>

#include "net_client.h"
#include "net_server.h"

void ns_process_callback(net_server_t *ns, net_client_t *nc, ns_status_e status)
{
    switch (status) {
    case NS_DISCONNECT_CLIENT:
        if (nc->disconnected)
            ns_remove_client(ns, nc);
        else
            ns_disconnect_client(ns, nc);
        break;
    case NS_CLOSE_CLIENT:
        ns_remove_client(ns, nc);
        break;
    case NS_CLOSE_SERVER:
        ns->running = false;
    default:
        break;
    }
}

void ns_set_callbacks(net_server_t *net_server, ns_callbacks_t callbacks)
{
    if (!net_server)
        return;
    memcpy(&net_server->callbacks, &callbacks, sizeof(ns_callbacks_t));
}

ns_callbacks_t *ns_get_callbacks(net_server_t *net_server)
{
    if (!net_server)
        return NULL;
    return &net_server->callbacks;
}