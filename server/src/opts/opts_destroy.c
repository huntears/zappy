/*
** EPITECH PROJECT, 2021
** OPTS_DESTROY
** File description:
** Opts_destroy function
*/

#include "opt.h"

void opts_destroy(struct opts *opts)
{
    if (opts->names)
        list_destroy(opts->names);
}