/*
** EPITECH PROJECT, 2019
** LIST_SET
** File description:
** List_set function
*/

#include <stddef.h>
#include "list.h"
#include "private_list.h"

int list_set(list_t *list, void *data, int index)
{
    list_it_t *element;

    if (!list)
        return (1);
    element = get_element(list, index);
    if (!element)
        return (1);
    element->data = data;
    return (0);
}

int list_replace(list_t *list, void *data, int index)
{
    list_it_t *element;

    if (!list)
        return (1);
    element = get_element(list, index);
    if (!element)
        return (1);
    destroy_data(list, element->data);
    element->data = data;
    return (0);
}