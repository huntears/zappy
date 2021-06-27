/*
** EPITECH PROJECT, 2021
** zappy_ai
** File description:
** send
*/

#include <Python.h>

#include "networking_module.h"

static void smart_write(int fd, void *data, size_t size)
{
    ssize_t written_size = 0;

    while (size) {
        written_size = write(fd, data, size);
        if (written_size == -1)
            continue;
        size -= (size_t)written_size;
        data = (char *)data + written_size;
    }
}

PyObject *zappy_send(PyObject *self, PyObject *args)
{
    int fd = 0;
    char *str = NULL;
    fd_set set;

    if (!PyArg_ParseTuple(args, "is", &fd, &str))
        return NULL;
    FD_ZERO(&set);
    FD_SET(fd, &set);
    if (select(fd + 1, NULL, &set, NULL, NULL) == -1)
        return NULL;
    else if (!FD_ISSET(fd, &set))
        return NULL;
    smart_write(fd, str, strlen(str));
    Py_INCREF(Py_None);
    return Py_None;
}
