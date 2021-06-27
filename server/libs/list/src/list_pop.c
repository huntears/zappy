/*
** EPITECH PROJECT, 2021
** LIST_POP
** File description:
** List_pop function
*/

#include <stdlib.h>
#include "list.h"
#include "private_list.h"

void *list_pop(list_t *list, int index)
{
    void *data;
    list_it_t *element;

    if (!list)
        return (NULL);
    element = get_element(list, index);
    if (!element)
        return (NULL);
    data = element->data;
    list_remove_link(list, element);
    free(element);
    list->size--;
    return (data);
}