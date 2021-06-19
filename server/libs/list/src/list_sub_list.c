/*
** EPITECH PROJECT, 2019
** LIST_SUB_LIST
** File description:
** List_sub_list function
*/

#include <stddef.h>
#include "list.h"

int list_sub_list(list_t *list, int index_from, int index_to)
{
    if (!list || index_from > index_to)
        return (1);
    if (index_from < 0 || index_from > list->size)
        return (1);
    if (index_to < 0 || index_to > list->size)
        return (1);
    list_remove_range(list, index_to + 1, list->size);
    list_remove_range(list, 0, index_from);
    return (0);
}