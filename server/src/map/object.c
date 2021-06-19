/*
** EPITECH PROJECT, 2021
** OBJECT
** File description:
** Object function
*/

#include <stdlib.h>
#include <string.h>

#include "object.h"

const struct object objects[] = {
    { FOOD, "food" },
    { LINEMATE, "linemate" },
    { DERAUMERE, "deraumere" },
    { SIBUR, "sibur" },
    { MENDIANE, "mendiane" },
    { PHIRAS, "phiras" },
    { THYSTAME, "thystame" },
    { UNKNOWN_OBJECT, "unknown" },
};

const float object_density[] = {
    0.5, // FOOD
    0.3, // LINEMATE
    0.15, // DERAUMERE
    0.1, // SIBUR
    0.1, // MENDIANE
    0.08, // PHIRAS
    0.05, // THYSTAME
};

enum object_type string_to_object(const char *str)
{
    for (size_t k = 0; k <= THYSTAME; k++)
        if (strcmp(str, objects[k].str) == 0)
            return objects[k].object;
    return UNKNOWN_OBJECT;
}

const char *object_to_string(enum object_type type)
{
    return objects[type].str;
}