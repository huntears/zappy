/*
** EPITECH PROJECT, 2019
** LIST_CONTAIN
** File description:
** List_contain function
*/

#include <stddef.h>
#include "list.h"

int list_contain(list_t *list, void *data)
{
    list_it_t *element;

    if (!list)
        return (0);
    element = list->list;
    while (element) {
        if (element->data == data)
            return (1);
        element = element->next;
    }
    return (0);
}