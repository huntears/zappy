/*
** EPITECH PROJECT, 2019
** LIST_CLONE
** File description:
** List_clone function
*/

#include <stddef.h>
#include <stdlib.h>
#include "list.h"
#include "private_list.h"

list_t *list_clone(list_t *list)
{
    list_it_t *element;
    list_t *clone;

    if (!list)
        return (NULL);
    element = list->list;
    clone = malloc(sizeof(list_t));
    clone->size = 0;
    clone->destructor = list->destructor;
    clone->list = NULL;
    clone->end = NULL;
    while (element) {
        list_add(clone, element->data);
        element = element->next;
    }
    return (clone);
}