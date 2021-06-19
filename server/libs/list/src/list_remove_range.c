/*
** EPITECH PROJECT, 2019
** LIST_REMOVE_RANGE
** File description:
** List_remove_range function
*/

#include <stdlib.h>
#include <stddef.h>
#include "list.h"
#include "private_list.h"

void list_remove_range_link(list_t *list,
    list_it_t *first_element_link, list_it_t *last_element_link)
{
    if (first_element_link)
        first_element_link->next = last_element_link;
    else
        list->list = last_element_link;
    if (last_element_link)
        last_element_link->prev = first_element_link;
    else
        list->end = first_element_link;
}

void list_remove_range_remove(list_t *list, list_it_t **next_element,
    int index_from, int index_to)
{
    list_it_t *element;

    for (int rm_count = 0; rm_count < index_to - index_from; rm_count++) {
        element = next_element[0];
        next_element[0] = next_element[0]->next;
        destroy_data(list, element->data);
        free(element);
        list->size--;
    }
}

int list_remove_range(list_t *list, int index_from, int index_to)
{
    list_it_t *first_element_link;
    list_it_t *next_element;

    if (!list || index_from > index_to)
        return (1);
    if (index_to < 0 || index_to > list->size)
        return (1);
    if (index_from == 0 && index_to == list->size)
        return (list_clear(list));
    next_element = get_element(list, index_from);
    if (!next_element)
        return (1);
    first_element_link = next_element->prev;
    list_remove_range_remove(list, &next_element, index_from, index_to);
    list_remove_range_link(list, first_element_link, next_element);
    return (0);
}