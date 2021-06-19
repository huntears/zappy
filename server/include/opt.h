/*
** EPITECH PROJECT, 2021
** OPT
** File description:
** Opt header
*/

#ifndef OPT_H_
#define OPT_H_

#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "list/list.h"

struct opts {
    uint16_t port;
    size_t width;
    size_t height;
    list_t *names;
    uint64_t max_clients;
    uint64_t frequency;
};

struct opt_key_func {
    char key;
    bool (*func)(struct opts *, char *const *);
};

bool parse_args(struct opts *opts, int argc, char *const *argv);
void opts_destroy(struct opts *opts);

bool opt_help(struct opts *opts, char *const *argv);
bool opt_port(struct opts *opts, char *const *argv);
bool opt_width(struct opts *opts, char *const *argv);
bool opt_height(struct opts *opts, char *const *argv);
bool opt_names(struct opts *opts, char *const *argv);
bool opt_clients(struct opts *opts, char *const *argv);
bool opt_freq(struct opts *opts, char *const *argv);

#endif /* !OPT_H_ */