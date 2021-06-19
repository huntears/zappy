/*
** EPITECH PROJECT, 2021
** CHUNKS
** File description:
** Chunks function
*/

#include <stdlib.h>
#include <string.h>

#include "map.h"

chunk_t **chunks_create(size_t width, size_t height)
{
    chunk_t **map = malloc(sizeof(chunk_t *) * (height + 1));

    if (!map)
        return NULL;
    for (size_t y = 0; y < height; y++) {
        map[y] = malloc(sizeof(chunk_t) * width);
        if (!map[y])
            return chunks_destroy(map);
        memset(map[y], 0, sizeof(chunk_t) * width);
    }
    map[height] = NULL;
    return map;
}

void *chunks_destroy(chunk_t **chunks)
{
    if (!chunks)
        return NULL;
    for (size_t y = 0; chunks[y]; y++)
        free(chunks[y]);
    free(chunks);
    return NULL;
}
