/*
** EPITECH PROJECT, 2021
** EGG
** File description:
** Egg header
*/

#ifndef EGG_H_
#define EGG_H_

#include <stdint.h>

#define TIME_BEFORE_EGG_SPAWN (600)

typedef struct egg {
    uint64_t id;
    uint64_t player_id;
    int x;
    int y;
    uint64_t time_to_hatching;
} egg_t;

// create / destroy
egg_t *egg_create(uint64_t player_id, int x, int y);
void *egg_destroy(egg_t *egg);

#endif /* !EGG_H_ */