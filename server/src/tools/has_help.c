/*
** EPITECH PROJECT, 2021
** HAS_HELP
** File description:
** Has_help function
*/

#include <string.h>

#include "tools/tools.h"

bool has_help(char *const *tab)
{
    for (int k = 0; tab[k]; k++) {
        if (strcmp(tab[k], "-h") == 0)
            return true;
        if (strcmp(tab[k], "--help") == 0)
            return true;
    }
    return false;
}