/*
** EPITECH PROJECT, 2021
** OPTS
** File description:
** Opts function
*/

#include <stdlib.h>
#include <string.h>

#include "opt.h"

static const struct option long_opt[] = {
    { "help", no_argument, NULL, 'h' },
    { "port", required_argument, NULL, 'p' },
    { "width", required_argument, NULL, 'x' },
    { "heigh", required_argument, NULL, 'y' },
    { "names", required_argument, NULL, 'n' },
    { "clients", required_argument, NULL, 'c' },
    { "freq", required_argument, NULL, 'f' },
    { NULL, 0, NULL, 0 },
};

static const struct opt_key_func opt_key_func[] = {
    { 'h', opt_help },
    { 'p', opt_port },
    { 'x', opt_width },
    { 'y', opt_height },
    { 'n', opt_names },
    { 'c', opt_clients },
    { 'f', opt_freq },
    { 0, NULL },
};

static bool add_default_team_names(struct opts *opts)
{
    char *tmpname;

    if (!(tmpname = strdup("Team1")) || list_add(opts->names, tmpname)) {
        free(tmpname);
        return false;
    }
    if (!(tmpname = strdup("Team2")) || list_add(opts->names, tmpname)) {
        free(tmpname);
        return false;
    }
    if (!(tmpname = strdup("Team3")) || list_add(opts->names, tmpname)) {
        free(tmpname);
        return false;
    }
    if (!(tmpname = strdup("Team4")) || list_add(opts->names, tmpname)) {
        free(tmpname);
        return false;
    }
    return true;
}

static bool opts_init(struct opts *opts)
{
    opts->port = 2222;
    opts->width = 10;
    opts->height = 10;
    opts->max_clients = 3;
    opts->frequency = 100;
    if (!(opts->names = list_create(&free)) || !add_default_team_names(opts))
        return false;
    return true;
}

static int get_opt_id(char c)
{
    for (size_t k = 0; opt_key_func[k].key; k++)
        if (c == opt_key_func[k].key)
            return k;
    return -1;
}

bool check_opts(int ac, char *const *av)
{
    if (ac != optind) {
        fprintf(stderr, "%s: too many argument\n", *av);
        fprintf(stderr, "Try '%s --help' for more information.\n", *av);
        return false;
    }
    return true;
}

bool parse_args(struct opts *opts, int ac, char *const *av)
{
    int opt_id;
    char c;

    if (!opts_init(opts))
        return false;
    while ((c = getopt_long(ac, av, "hp:x:y:n:c:f:", long_opt, NULL)) != -1) {
        opt_id = get_opt_id(c);
        if (opt_id == -1) {
            fprintf(stderr, "Try '%s --help' for more information.\n", *av);
            return false;
        }
        if (!opt_key_func[opt_id].func(opts, av)) {
            fprintf(stderr, "Try '%s --help' for more information.\n", *av);
            return false;
        }
    }
    return check_opts(ac, av);
}