/*
** EPITECH PROJECT, 2021
** OBJECT
** File description:
** Object header
*/

#ifndef OBJECT_H_
#define OBJECT_H_

#define NB_OBJECTS (7)

enum object_type {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    UNKNOWN_OBJECT,
};

struct object {
    enum object_type object;
    char str[10];
};

// in object.c
extern const float object_density[];

enum object_type string_to_object(const char *str);
const char *object_to_string(enum object_type type);

#endif /* !OBJECT_H_ */