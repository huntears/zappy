/*
** EPITECH PROJECT, 2021
** LIST_ITERATOR
** File description:
** List_iterator function
*/

#include <stdbool.h>
#include <stddef.h>

#include "list.h"

list_it_t *list_get_it(list_t *list)
{
    if (!list)
        return NULL;
    return list->list;
}

bool next_it(list_it_t **list_it)
{
    if (!list_it || !*list_it)
        return false;
    *list_it = (*list_it)->next;
    if (!*list_it)
        return false;
    return true;
}