/*
** EPITECH PROJECT, 2021
** CLIENT_CHOSE_TEAM
** File description:
** Client_chose_team function
*/

#include <string.h>

#include "tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

static bool init_ai(
    zappy_server_t *server, zappy_client_t *client, team_t *team)
{
    if (!team_can_ai_spawn(team))
        return false;
    client->ai = zappy_ai_create(server, team);
    if (!client->ai)
        return false;
    client->type = CLIENT_AI;
    team_spawn_ai(team, &client->ai->x, &client->ai->y);
    cmd_ai_connect_nbr(server, client, NULL);
    zc_send(client, "%d %d\n", server->map->width, server->map->height);
    send_gui_pin(server, client);
    return true;
}

static bool init_gui(zappy_server_t *server, zappy_client_t *client)
{
    cmd_gui_msz(server, client, NULL);
    cmd_gui_sgt(server, client, NULL);
    cmd_gui_mct(server, client, NULL);
    cmd_gui_tna(server, client, NULL);
    return true;
}

bool client_chose_team(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    if (strcmp(line, "GRAPHIC") == 0) {
        client->type = CLIENT_GRAPHIC;
        return init_gui(server, client);
        return true;
    }
    for (size_t team_id = 0; server->teams[team_id]; team_id++)
        if (strcmp(line, server->teams[team_id]->name) == 0)
            return init_ai(server, client, server->teams[team_id]);
    return false;
}