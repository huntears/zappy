/*
** EPITECH PROJECT, 2021
** zappy_ai
** File description:
** disconnect
*/

#include <unistd.h>

#include <Python.h>

#include "networking_module.h"

PyObject *zappy_disconnect(PyObject *self, PyObject *args)
{
    int fd = 0;

    if (!PyArg_ParseTuple(args, "i", &fd))
        return NULL;
    close(fd);
    return Py_None;
}
