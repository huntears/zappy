/*
** EPITECH PROJECT, 2021
** EGG
** File description:
** Egg function
*/

#include <stdlib.h>

#include "egg.h"

egg_t *egg_create(uint64_t player_id, int x, int y)
{
    static uint64_t id = 0;
    egg_t *egg = malloc(sizeof(egg_t));

    if (!egg)
        return NULL;
    egg->id = id;
    egg->player_id = player_id;
    egg->x = x;
    egg->y = y;
    egg->time_to_hatching = 600;
    id++;
    return egg;
}

void *egg_destroy(egg_t *egg)
{
    if (!egg)
        return NULL;
    free(egg);
    return NULL;
}
