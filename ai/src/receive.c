/*
** EPITECH PROJECT, 2021
** zappy_ai
** File description:
** receive
*/

#include <Python.h>

#include "networking_module.h"

PyObject *zappy_receive(PyObject *self, PyObject *args)
{
    int fd = 0;
    char buffer[1025] = {0};
    fd_set set;
    int ret_read;

    if (!PyArg_ParseTuple(args, "i", &fd))
        return NULL;
    FD_ZERO(&set);
    FD_SET(fd, &set);
    if (select(fd + 1, &set, NULL, NULL, NULL) == -1)
        return NULL;
    else if (!FD_ISSET(fd, &set))
        return NULL;
    ret_read = read(fd, buffer, 1024);
    if (ret_read == 0 || ret_read == -1)
        return NULL;
    return PyUnicode_FromString(buffer);
}
