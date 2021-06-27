/*
** EPITECH PROJECT, 2021
** MAIN
** File description:
** Main function
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "opt.h"
#include "tools/tools.h"

#include "zappy_server.h"

static const char HELP_STRING[] =
    "USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c "
    "clientsNb -f freq\n"
    "\t-p / --port\tport number\n"
    "\t-x / --width\twidth of the world\n"
    "\t-y / --height\theight of the world\n"
    "\t-n / --names\tname of the team X\n"
    "\t-c / --clients\tnumber of authorized clients per team\n"
    "\t-f / --freq\treciprocal of time unit for execution of actions\n";

static void print_levels(team_t *team)
{
    size_t *levels = team->levels;

    printf("%s -> %zu %zu %zu %zu %zu %zu %zu %zu\n", team->name, levels[0],
        levels[1], levels[2], levels[3], levels[4], levels[5], levels[6],
        levels[7]);
}

static void display_winning_team(zappy_server_t *server)
{
    for (size_t team_id = 0; server->teams[team_id]; team_id++)
        print_levels(server->teams[team_id]);
    for (size_t team_id = 0; server->teams[team_id]; team_id++) {
        if (server->teams[team_id]->levels[7]) {
            printf("Winning team: %s\n", server->teams[team_id]->name);
        }
    }
}

bool prepare_zappy_server(struct opts *opts)
{
    zappy_server_t *server = zappy_server_create(opts);

    if (!server)
        return false;
    srand(time(NULL));
    signal(SIGINT, signal_handler);
    signal(SIGPIPE, signal_handler);
    signal(SIGTERM, signal_handler);
    ns_set_timeval_callback(
        server->net_server, 1000000 / server->frequency, &on_timeval);
    ns_run(server->net_server);
    display_winning_team(server);
    zappy_server_destroy(server);
    return true;
}

int main(int argc, char *const *argv)
{
    struct opts opts;

    if (has_help(argv)) {
        printf("%s", HELP_STRING);
        return EXIT_SUCCESS;
    }
    if (!parse_args(&opts, argc, argv)) {
        opts_destroy(&opts);
        return 84;
    }
    if (!prepare_zappy_server(&opts)) {
        opts_destroy(&opts);
        return 84;
    }
    opts_destroy(&opts);
    return EXIT_SUCCESS;
}