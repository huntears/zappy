/*
** EPITECH PROJECT, 2019
** LIST_ADD
** File description:
** List_add function
*/

#include <stddef.h>
#include <stdlib.h>
#include "list.h"
#include "private_list.h"

int list_add(list_t *list, void *data)
{
    list_it_t *element;

    if (!list)
        return (1);
    element = create_element(data);
    if (!element)
        return (1);
    if (list->end) {
        element->prev = list->end;
        list->end->next = element;
        list->end = element;
    }
    else {
        list->list = element;
        list->end = element;
    }
    list->size++;
    return (0);
}

void list_add_at_link(list_t *list, list_it_t *at, list_it_t *element)
{
    element->prev = at->prev;
    if (at->prev)
        element->prev->next = element;
    else
        list->list = element;
    element->next = at;
    at->prev = element;
    list->size++;
}

int list_add_at(list_t *list, void *data, int index)
{
    list_it_t *element;
    list_it_t *at;

    if (!list)
        return (1);
    if (index == list->size)
        return (list_add(list, data));
    at = get_element(list, index);
    if (!at)
        return (1);
    element = create_element(data);
    if (!element)
        return (1);
    list_add_at_link(list, at, element);
    return (0);
}