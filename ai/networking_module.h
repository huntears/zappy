/*
** EPITECH PROJECT, 2021
** zappy_ai
** File description:
** networking_module
*/

#ifndef NETWORKING_MODULE_H_
    #define NETWORKING_MODULE_H_

    #include <netdb.h>

    #include <Python.h>

    typedef struct client_s {
        struct sockaddr_in addr;
        int sockfd;
    } client_t;

    PyObject *zappy_send(PyObject *self, PyObject *args);
    PyObject *zappy_receive(PyObject *self, PyObject *args);
    PyObject *zappy_disconnect(PyObject *self, PyObject *args);
    PyObject *zappy_connect(PyObject *self, PyObject *args);

#endif /* !NETWORKING_MODULE_H_ */
