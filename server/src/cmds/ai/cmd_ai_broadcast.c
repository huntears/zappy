/*
** EPITECH PROJECT, 2021
** CMD_AI_BROADCAST
** File description:
** CMD_ai_broadcast function
*/

#include <math.h>

#include "tools/math.h"
#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

static const int pos_to_dir[][2] = {
    { 0, -1 },
    { 1, 0 },
    { 0, 1 },
    { -1, 0 },
};

static double calc_angle_in_torus(
    zappy_client_t *from, zappy_client_t *to, int width, int height)
{
    double x1 = to->ai->x;
    double y1 = to->ai->y;
    double x2 = from->ai->x;
    double y2 = from->ai->y;
    double x3;
    double y3;
    double rad_angle;

    if (GET_DIST_P(to->ai->x, x2) > GET_DIST_P(to->ai->x - width, x2))
        x1 = to->ai->x - width;
    if (GET_DIST_P(to->ai->x, x2) > GET_DIST_P(to->ai->x + width, x2))
        x1 = to->ai->x + width;
    if (GET_DIST_P(to->ai->y, y2) > GET_DIST_P(to->ai->y - height, y2))
        y1 = to->ai->y - height;
    if (GET_DIST_P(to->ai->y, y2) > GET_DIST_P(to->ai->y + height, y2))
        y1 = to->ai->y + height;
    x3 = x1 + pos_to_dir[to->ai->direction][0];
    y3 = y1 + pos_to_dir[to->ai->direction][1];
    rad_angle = atan2(y3 - y1, x3 - x1) - atan2(y2 - y1, x2 - x1);
    return ((int) (rad_angle * (180.0 / M_PI)) + 360) % 360;
}

static int get_send_dir(
    zappy_server_t *server, zappy_client_t *from, zappy_client_t *to)
{
    double angle;

    if (from->ai->x == to->ai->x && from->ai->y == to->ai->y)
        return 0;
    angle = calc_angle_in_torus(
        from, to, (int) server->map->width, (int) server->map->width);
    return round(angle / 45.0) + 1;
}

void cmd_ai_broadcast(
    zappy_server_t *server, zappy_client_t *client, const char *line)
{
    const char *msg = &line[10];

    ITERATE_AIS(ai, server)
    {
        if (ai == client)
            continue;
        zc_send(ai, "message %d, %s\n", get_send_dir(server, client, ai), msg);
    }
    send_gui_pbc(server, client->ai->id, msg);
    zc_send_line(client, AI_OK);
}