/*
** EPITECH PROJECT, 2021
** MAP
** File description:
** Map function
*/

#include <stdlib.h>
#include <string.h>

#include "opt.h"

#include "map.h"
#include "server_cmds.h"
#include "zappy_server.h"

static void init_map(map_t *map, size_t width, size_t height)
{
    size_t nb_objects;

    for (size_t object_id = 0; object_id < NB_OBJECTS; object_id++) {
        nb_objects = width * height * object_density[object_id];
        for (size_t k = 0; k < nb_objects; k++) {
            map->chunks[rand() % height][rand() % width].objects[object_id]++;
        }
        map->object_count[object_id] = nb_objects;
    }
}

map_t *map_create(size_t width, size_t height)
{
    map_t *map = malloc(sizeof(map_t));

    if (!map)
        return NULL;
    memset(map, 0, sizeof(chunk_t));
    map->width = width;
    map->height = height;
    map->chunks = chunks_create(width, height);
    map->time_before_object_spawn = TIME_BEFORE_OBJECT_SPAWN;
    if (!map->chunks)
        return map_destroy(map);
    init_map(map, width, height);
    return map;
}

void *map_destroy(map_t *map)
{
    if (!map)
        return NULL;
    if (map->chunks)
        chunks_destroy(map->chunks);
    free(map);
    return NULL;
}

chunk_t *map_get_chunk(map_t *map, int x, int y)
{
    return &map->chunks[MOD(y, map->height)][MOD(x, map->width)];
}

void map_spawn_objects(map_t *map, zappy_server_t *zappy_server)
{
    int x;
    int y;

    if (map->time_before_object_spawn > 1) {
        map->time_before_object_spawn--;
        return;
    }
    map->time_before_object_spawn = TIME_BEFORE_OBJECT_SPAWN;
    for (size_t object_id = 0; object_id < NB_OBJECTS; object_id++) {
        while (map->object_count[object_id]
            < map->width * map->height * object_density[object_id]) {
            x = rand() % map->width;
            y = rand() % map->height;
            map->chunks[y][x].objects[object_id]++;
            map->object_count[object_id]++;
            send_gui_bct(zappy_server, x, y);
        }
    }
}