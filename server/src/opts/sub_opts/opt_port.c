/*
** EPITECH PROJECT, 2021
** OPT_PORT
** File description:
** Opt_port function
*/

#include <stdio.h>

#include "tools/tools.h"

#include "opt.h"

bool opt_port(struct opts *opts, char *const *argv)
{
    int got;

    UNUSED(argv);
    if (!super_atoi(optarg, &got) || got < 0 || got >= 0xffff) {
        fprintf(stderr,
            "Expected a positive decimal short argument to "
            "--port, but got '%s'\n",
            optarg);
        return false;
    }
    opts->port = got;
    return true;
}