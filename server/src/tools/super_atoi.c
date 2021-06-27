/*
** EPITECH PROJECT, 2021
** SUPER_ATOI
** File description:
** Super_atoi function
*/

#include <stdio.h>

#include "tools/tools.h"

bool super_atoi(const char *str, int *value)
{
    char after;

    if (sscanf(str, "%d%c", value, &after) == 1)
        return true;
    return false;
}