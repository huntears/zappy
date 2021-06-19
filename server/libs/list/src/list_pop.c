/*
** EPITECH PROJECT, 2021
** LIST_POP
** File description:
** List_pop function
*/

#include <stddef.h>
#include "list.h"

void *list_pop(list_t *list, int index)
{
    void *data = list_get(list, index);

    list_remove(list, index);
    return (data);
}