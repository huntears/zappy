/*
** EPITECH PROJECT, 2021
** OPT_HEIGHT
** File description:
** Opt_height function
*/

#include <stdio.h>

#include "tools/tools.h"

#include "opt.h"

bool opt_height(struct opts *opts, char *const *argv)
{
    int got;

    UNUSED(argv);
    if (!super_atoi(optarg, &got) || got < 10) {
        fprintf(stderr,
            "Expected a positive decimal integer equal or upper than 10 as "
            "argument to --height, but got '%s'\n",
            optarg);
        return false;
    }
    opts->height = got;
    return true;
}