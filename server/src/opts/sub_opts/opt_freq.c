/*
** EPITECH PROJECT, 2021
** OPT_FREQ
** File description:
** Opt_freq function
*/

#include <stdio.h>

#include "tools.h"

#include "opt.h"

bool opt_freq(struct opts *opts, char *const *argv)
{
    int got;

    UNUSED(argv);
    if (!super_atoi(optarg, &got) || got < 1 || got > 10000) {
        fprintf(stderr,
            "Expected a positive decimal integer between 1 and 10000 argument "
            "to --freq, but got '%s'\n",
            optarg);
        return false;
    }
    opts->frequency = got;
    return true;
}