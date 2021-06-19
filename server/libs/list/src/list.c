/*
** EPITECH PROJECT, 2019
** LIST
** File description:
** List create & destroy function
*/

#include <stddef.h>
#include <stdlib.h>
#include "list.h"
#include "private_list.h"

list_t *list_create(void (*destructor)(void *))
{
    list_t *list = malloc(sizeof(list_t));

    if (!list)
        return (NULL);
    list->size = 0;
    list->destructor = destructor;
    list->list = NULL;
    list->end = NULL;
    return (list);
}

list_it_t *create_element(void *data)
{
    list_it_t *element = malloc(sizeof(list_it_t));

    if (!element)
        return (NULL);
    element->data = data;
    element->prev = NULL;
    element->next = NULL;
    return (element);
}

int list_clear(list_t *list)
{
    list_it_t *end;
    list_it_t *to_free;

    if (!list)
        return (1);
    end = list->end;
    if (!end)
        return (0);
    do {
        to_free = end;
        end = end->prev;
        destroy_data(list, to_free->data);
        free(to_free);
    }
    while (end);
    list->size = 0;
    list->list = NULL;
    list->end = NULL;
    return (0);
}

void *list_destroy(list_t *list)
{
    if (!list)
        return (NULL);
    list_clear(list);
    free(list);
    return (NULL);
}