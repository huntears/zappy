/*
** EPITECH PROJECT, 2021
** EGG
** File description:
** Egg header
*/
#ifndef EGG_H_
#define EGG_H_

typedef struct egg {
    int x;
    int y;
} egg_t;

// create / destroy
egg_t *egg_create(int x, int y);
void *egg_destroy(egg_t *egg);

#endif /* !EGG_H_ */