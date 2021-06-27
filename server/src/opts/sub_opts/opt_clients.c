/*
** EPITECH PROJECT, 2021
** OPT_CLIENTS
** File description:
** Opt_clients function
*/

#include <stdio.h>

#include "tools/tools.h"

#include "opt.h"

bool opt_clients(struct opts *opts, char *const *argv)
{
    int got;

    UNUSED(argv);
    if (!super_atoi(optarg, &got) || got <= 0) {
        fprintf(stderr,
            "Expected a positive decimal not null integer argument to "
            "--freq, but got '%s'\n",
            optarg);
        return false;
    }
    opts->max_clients = got;
    return true;
}