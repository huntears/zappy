/*
** EPITECH PROJECT, 2019
** LIST_REVERSE
** File description:
** List_reverse function
*/

#include <stddef.h>
#include "list.h"

int list_reverse(list_t *list)
{
    void *tmp;
    list_it_t *start;
    list_it_t *end;

    if (!list)
        return (1);
    start = list->list;
    end = list->end;
    for (int k = 0; k < list->size / 2; k++) {
        tmp = start->data;
        start->data = end->data;
        end->data = tmp;
        start = start->next;
        end = end->prev;
    }
    return (0);
}