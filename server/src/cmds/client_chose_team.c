/*
** EPITECH PROJECT, 2021
** CLIENT_CHOSE_TEAM
** File description:
** Client_chose_team function
*/

#include <string.h>

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

static bool init_ai(
    zappy_server_t *server, zappy_client_t *client, team_t *team)
{
    static size_t ai_id = 0;
    if (!team_can_ai_spawn(team))
        return false;
    client->ai = zappy_ai_create(server, team, ai_id);
    if (!client->ai)
        return false;
    ai_id++;
    client->type = CLIENT_AI;
    printf("New AI: %lu\n", client->ai->id);
    cmd_ai_connect_nbr(server, client, NULL);
    zc_send(client, "%zu %zu\n", server->map->width, server->map->height);
    team_spawn_ai(team, server, &client->ai->x, &client->ai->y);
    send_gui_pnw(server, client);
    send_gui_pin(server, client);
    return true;
}

static void init_gui(zappy_server_t *server, zappy_client_t *client)
{
    ITERATE_AIS(ai, server) {
        send_gui_pnw_to(client, ai);
        send_gui_pin_to(client, ai);
        if (ai->ai->is_incantated)
            send_gui_pnw_to(client, ai);
        if (ai->ai->is_fork)
            send_gui_pfk_to(client, ai->ai->id);
    }
    for (size_t team_id = 0; server->teams[team_id]; team_id++) {
        ITERATE_EGGS(hatching_egg, server->teams[team_id]->hatching_eggs) {
            send_gui_enw_to(client, hatching_egg);
        }
        ITERATE_EGGS(hatched_egg, server->teams[team_id]->hatched_eggs) {
            send_gui_enw_to(client, hatched_egg);
            send_gui_eht_to(client, hatched_egg->id);
        }
    }
}

bool client_chose_team(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    if (strcmp(line, "GRAPHIC") == 0) {
        printf("New GUI\n");
        client->type = CLIENT_GRAPHIC;
        cmd_gui_msz(server, client, NULL);
        cmd_gui_sgt(server, client, NULL);
        cmd_gui_mct(server, client, NULL);
        cmd_gui_tna(server, client, NULL);
        init_gui(server, client);
        return true;
    }
    for (size_t team_id = 0; server->teams[team_id]; team_id++)
        if (strcmp(line, server->teams[team_id]->name) == 0)
            return init_ai(server, client, server->teams[team_id]);
    return false;
}