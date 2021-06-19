/*
** EPITECH PROJECT, 2019
** LIST_COUNT
** File description:
** List_count function
*/

#include <stddef.h>
#include "list.h"

int list_count(list_t *list, void *data)
{
    list_it_t *element;
    int occurrence = 0;

    if (!list)
        return (-1);
    element = list->list;
    while (element) {
        if (element->data == data)
            occurrence++;
        element = element->next;
    }
    return (occurrence);
}