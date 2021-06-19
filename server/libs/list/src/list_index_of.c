/*
** EPITECH PROJECT, 2019
** LIST_INDEX_OF
** File description:
** List_index_of function
*/

#include <stddef.h>
#include "list.h"

int list_index_of(list_t *list, void *data)
{
    list_it_t *element;
    int index = 0;

    if (!list)
        return (-1);
    element = list->list;
    while (element) {
        if (element->data == data)
            return (index);
        element = element->next;
        index++;
    }
    return (-1);
}

int list_last_index_of(list_t *list, void *data)
{
    list_it_t *element;
    int index;

    if (!list)
        return (-1);
    index = list->size - 1;
    element = list->end;
    while (element) {
        if (element->data == data)
            return (index);
        element = element->prev;
        index--;
    }
    return (-1);
}