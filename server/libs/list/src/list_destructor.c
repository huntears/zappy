/*
** EPITECH PROJECT, 2019
** LIST_DESTRUCTOR
** File description:
** List_destructor function
*/

#include <stddef.h>
#include <stdlib.h>
#include "list.h"
#include "private_list.h"

void (*list_get_destructor(list_t *list))(void *)
{
    if (!list)
        return (NULL);
    return (list->destructor);
}

int list_set_destructor(list_t *list, void (*destructor)(void *))
{
    if (!list)
        return (1);
    list->destructor = destructor;
    return (0);
}

void destroy_data(list_t *list, void *data)
{
    if (!list->destructor)
        return;
    (*(list->destructor))(data);
}