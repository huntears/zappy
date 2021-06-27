/*
** EPITECH PROJECT, 2021
** ZAPPY_AI_CONSUME_TIME
** File description:
** Zappy_ai_consume_time function
*/

#include <stdlib.h>
#include <string.h>

#include "server_cmds.h"
#include "zappy_ai.h"
#include "zappy_server.h"

static bool zappy_ai_consume_food(
    zappy_server_t *server, zappy_client_t *client, size_t consume_time)
{
    if (client->ai->remaining_time <= consume_time) {
        if (client->ai->inventory[FOOD] == 0) {
            client->ai->remaining_time = 0;
            zappy_ai_die(client, server);
        } else {
            client->ai->inventory[FOOD]--;
            client->ai->remaining_time += REMAINING_TIME_PER_FOOD;
            return zappy_ai_consume_time(server, client, consume_time);
        }
    } else
        client->ai->remaining_time -= consume_time;
    return client->ai->is_alive;
}

static int get_cmd_ai_index(const char *line)
{
    size_t cmd_len;

    for (size_t k = 0; line && server_ai_cmds[k].cmd; k++) {
        cmd_len = strlen(server_ai_cmds[k].key);
        if (strncmp(server_ai_cmds[k].key, line, cmd_len))
            continue;
        if (server_ai_cmds[k].required_arguments && line[cmd_len] != ' ')
            break;
        if (!server_ai_cmds[k].required_arguments && line[cmd_len] != '\0')
            break;
        return k;
    }
    return -1;
}

static int get_cmd_ai_index_and_check(zappy_client_t *client, const char *line)
{
    int cmd_id;

    if (!line || client->ai->commands.commands_queue->size == 0)
        return -1;
    cmd_id = get_cmd_ai_index(line);
    if (cmd_id == -1) {
        list_remove(client->ai->commands.commands_queue, 0);
        zc_send_line(client, AI_KO);
        return -1;
    }
    return cmd_id;
}

static void zappy_ai_consume_cmds(
    zappy_server_t *server, zappy_client_t *client, size_t consume_time)
{
    const char *line = list_get(client->ai->commands.commands_queue, 0);
    int cmd_id = get_cmd_ai_index_and_check(client, line);
    struct zappy_ai_cmd *commands = &client->ai->commands;

    if (cmd_id == -1)
        return;
    if (commands->time_before_cmd_execution == -1) {
        if (server_ai_cmds[cmd_id].pre_cmd)
            server_ai_cmds[cmd_id].pre_cmd(server, client, line);
        commands->time_before_cmd_execution = server_ai_cmds[cmd_id].time_limit;
        zappy_ai_consume_cmds(server, client, consume_time);
    } else if (commands->time_before_cmd_execution <= (int) consume_time) {
        consume_time -= commands->time_before_cmd_execution;
        commands->time_before_cmd_execution = -1;
        server_ai_cmds[cmd_id].cmd(server, client, line);
        list_remove(commands->commands_queue, 0);
        zappy_ai_consume_cmds(server, client, consume_time);
    } else
        commands->time_before_cmd_execution -= consume_time;
}

bool zappy_ai_consume_time(
    zappy_server_t *server, zappy_client_t *client, size_t consume_time)
{
    if (!zappy_ai_consume_food(server, client, consume_time))
        return false;
    zappy_ai_consume_cmds(server, client, consume_time);
    return true;
}