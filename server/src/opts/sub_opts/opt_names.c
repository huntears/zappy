/*
** EPITECH PROJECT, 2021
** OPT_NAMES
** File description:
** Opt_names function
*/

#include <string.h>

#include "opt.h"

bool is_already_team_name_exist(list_t *team_names, const char *team_name)
{
    LIST_ITERATE(it, team_names)
    {
        if (it->data && strcmp(it->data, team_name) == 0)
            return true;
    }
    return false;
}

bool opt_names(struct opts *opts, char *const *argv)
{
    char *name;

    while (1) {
        if (is_already_team_name_exist(opts->names, argv[optind - 1])) {
            fprintf(stderr, "Team name '%s' already exist\n", argv[optind - 1]);
            return false;
        }
        if (strcmp(argv[optind - 1], "GRAPHIC") == 0) {
            fprintf(stderr, "Team name cannot be 'GRAPHIC' (reserver)\n");
            return false;
        }
        name = strdup(argv[optind - 1]);
        if (!name)
            return false;
        list_add(opts->names, name);
        if (!argv[optind] || argv[optind][0] == '-')
            break;
        optind++;
    }
    return true;
}