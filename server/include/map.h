/*
** EPITECH PROJECT, 2021
** MAP
** File description:
** Map header
*/

#ifndef MAP_H_
#define MAP_H_

#include <stdint.h>

#include "tools/math.h"

#include "object.h"

#define TIME_BEFORE_OBJECT_SPAWN (20)

typedef struct zappy_server zappy_server_t;

typedef struct chunk {
    uint64_t objects[NB_OBJECTS];
    uint64_t nb_players;
} chunk_t;

typedef struct map {
    size_t width;
    size_t height;
    chunk_t **chunks;
    uint64_t object_count[NB_OBJECTS];
    time_t time_before_object_spawn;

} map_t;

// chunks
chunk_t **chunks_create(size_t width, size_t height);
void *chunks_destroy(chunk_t **chunks);

// create / destroy
map_t *map_create(size_t width, size_t height);
void *map_destroy(map_t *map);

chunk_t *map_get_chunk(map_t *map, int x, int y);
void map_spawn_objects(map_t *map, zappy_server_t *zappy_server);

#endif /* !MAP_H_ */