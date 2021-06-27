/*
** EPITECH PROJECT, 2021
** STR2D
** File description:
** Str2d function
*/

#include <string.h>

#include "tools/tools.h"

size_t str2d_len(char *const *array)
{
    size_t len = 0;

    if (!array)
        return 0;
    while (*array) {
        array++;
        len++;
    }
    return len;
}

char **str2d_append(char **array, const char *str)
{
    char **tmp = array;
    size_t nb_str = str2d_len(array);

    array = malloc(sizeof(char *) * (nb_str + 1 + 1));
    if (!array)
        return str2d_free(tmp);
    for (size_t k = 0; tmp && tmp[k]; k++)
        array[k] = tmp[k];
    if (str)
        array[nb_str] = strdup(str);
    else
        array[nb_str] = NULL;
    array[nb_str + 1] = NULL;
    free(tmp);
    if (str && !array[nb_str])
        return str2d_free(array);
    return array;
}

void *str2d_free(char **array)
{
    if (!array)
        return NULL;
    for (size_t k = 0; array[k]; k++)
        free(array[k]);
    free(array);
    return NULL;
}