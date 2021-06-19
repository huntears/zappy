/*
** EPITECH PROJECT, 2019
** LIST_TO_ARRAY
** File description:
** List_to_array function
*/

#include <stddef.h>
#include <stdlib.h>
#include "list.h"

void **list_to_array(list_t *list)
{
    list_it_t *element;
    void **array;
    int size;

    if (!list)
        return (NULL);
    element = list->list;
    size = list->size;
    array = malloc(sizeof(void *) * (size + 1));
    for (int index = 0; index < size; index++) {
        array[index] = element->data;
        element = element->next;
    }
    array[size] = NULL;
    return (array);
}