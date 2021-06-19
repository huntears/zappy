/*
** EPITECH PROJECT, 2021
** MAP
** File description:
** Map header
*/

#ifndef MAP_H_
#define MAP_H_

#include <stdint.h>

#include "object.h"

#define MOD(a, b) ((((a) % (int) (b)) + (int) (b)) % (int) (b))

typedef struct zappy_server zappy_server_t;

typedef struct chunk {
    size_t objects[NB_OBJECTS];
    size_t nb_players;
} chunk_t;

typedef struct map {
    size_t width;
    size_t height;
    chunk_t **chunks;
    size_t object_count[NB_OBJECTS];
} map_t;

// chunks
chunk_t **chunks_create(size_t width, size_t height);
void *chunks_destroy(chunk_t **chunks);

// create / destroy
map_t *map_create(size_t width, size_t height);
void *map_destroy(map_t *map);

chunk_t *map_get_chunk(map_t *map, int x, int y);

#endif /* !MAP_H_ */