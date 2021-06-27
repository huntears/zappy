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
    0.5,
    0.3,
    0.15,
    0.1,
    0.1,
    0.08,
    0.05,
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