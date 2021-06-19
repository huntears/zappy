/*
** EPITECH PROJECT, 2021
** zappy_ai
** File description:
** connect
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <Python.h>

#include "networking_module.h"

static client_t create_client(const char *ip, int port)
{
    client_t cli = {
        .sockfd = socket(AF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto)
    };

    cli.addr.sin_addr.s_addr = inet_addr(inet_ntoa(
        *(struct in_addr *)*(gethostbyname(ip)->h_addr_list)));
    cli.addr.sin_family = AF_INET;
    cli.addr.sin_port = htons(port);
    return cli;
}

PyObject *zappy_connect(PyObject *self, PyObject *args)
{
    char *ip = NULL;
    int port = 0;
    client_t cli;
    int ret_value = 0;

    if (!PyArg_ParseTuple(args, "si", &ip, &port))
        return NULL;
    cli = create_client(ip, port);
    ret_value = connect(cli.sockfd, (struct sockaddr *)&cli.addr,
        sizeof(cli.addr));
    if (ret_value == -1)
        return PyErr_SetFromErrno(PyExc_ConnectionError);
    return PyLong_FromLong(cli.sockfd);
}
