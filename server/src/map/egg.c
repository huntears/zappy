/*
** EPITECH PROJECT, 2021
** EGG
** File description:
** Egg function
*/

#include <stdlib.h>

#include "egg.h"

egg_t *egg_create(int x, int y)
{
    egg_t *egg = malloc(sizeof(egg_t));

    if (!egg)
        return NULL;
    egg->x = x;
    egg->y = y;
    return NULL;
}

void *egg_destroy(egg_t *egg)
{
    if (!egg)
        return NULL;
    free(egg);
    return NULL;
}
