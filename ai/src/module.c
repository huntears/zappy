/*
** EPITECH PROJECT, 2021
** zappy_ai
** File description:
** module
*/

#include <Python.h>

#include "networking_module.h"

static PyMethodDef methods[] = {
    {"send", zappy_send, METH_VARARGS, ""},
    {"receive", zappy_receive, METH_VARARGS, ""},
    {"disconnect", zappy_disconnect, METH_VARARGS,
        "Disconnect from server"},
    {"connect", zappy_connect, METH_VARARGS, "Connect to server"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "zappy_networking",
    "Python interface for socket networking",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_zappy_networking(void)
{
    return PyModule_Create(&module);
}
