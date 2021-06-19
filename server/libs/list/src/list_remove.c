/*
** EPITECH PROJECT, 2019
** LIST_REMOVE
** File description:
** List_remove function
*/

#include <stddef.h>
#include <stdlib.h>
#include "list.h"
#include "private_list.h"

void list_remove_link(list_t *list, list_it_t *element)
{
    if (element->prev)
        element->prev->next = element->next;
    else
        list->list = element->next;
    if (element->next)
        element->next->prev = element->prev;
    else
        list->end = element->prev;
}

int list_remove(list_t *list, int index)
{
    list_it_t *element;

    if (!list)
        return (1);
    element = get_element(list, index);
    if (!element)
        return (1);
    list_remove_link(list, element);
    destroy_data(list, element->data);
    free(element);
    list->size--;
    return (0);
}

int list_remove_data(list_t *list, void *data)
{
    list_it_t *next_element;
    list_it_t *element;

    if (!list)
        return (1);
    next_element = list->list;
    while (next_element) {
        element = next_element;
        next_element = next_element->next;
        if (element->data == data) {
            list_remove_link(list, element);
            destroy_data(list, element->data);
            free(element);
            list->size--;
            return (0);
        }
    }
    return (0);
}

int list_remove_all_data(list_t *list, void *data)
{
    list_it_t *next_element;
    list_it_t *element;

    if (!list)
        return (1);
    if (!list->list)
        return (0);
    next_element = list->list;
    do {
        element = next_element;
        next_element = next_element->next;
        if (element->data == data) {
            list_remove_link(list, element);
            destroy_data(list, element->data);
            free(element);
            list->size--;
        }
    }
    while (next_element);
    return (0);
}