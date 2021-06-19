/*
** EPITECH PROJECT, 2019
** LIST_GET
** File description:
** List_get function
*/

#include <stddef.h>
#include "list.h"

list_it_t *get_element(list_t *list, int index)
{
    list_it_t *element;

    if (!list)
        return (NULL);
    if (index < 0 || index >= list->size)
        return (NULL);
    element = list->list;
    for (int id = 0; id < index; id++)
        element = element->next;
    return (element);
}

void *list_get(list_t *list, int index)
{
    list_it_t *element;

    if (!list)
        return (NULL);
    element = get_element(list, index);
    if (!element)
        return (NULL);
    return (element->data);
}