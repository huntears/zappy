/*
** EPITECH PROJECT, 2021
** TOOLS
** File description:
** Tools header
*/

#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdbool.h>
#include <stdlib.h>

#define UNUSED(var) ((void) (var))

// str2d
size_t str2d_len(char *const *array);
char **str2d_append(char **array, const char *str);
void *str2d_free(char **array);

// other
bool super_atoi(const char *str, int *value);

bool has_help(char *const *tab);

void signal_handler(int signal);

#endif /* !TOOLS_H_ */