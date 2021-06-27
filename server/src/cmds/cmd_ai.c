/*
** EPITECH PROJECT, 2021
** CMD_AI
** File description:
** CMD_ai function
*/

#include <string.h>

#include "tools/tools.h"

#include "server_cmds.h"
#include "zappy_server.h"

const struct server_ai_cmd server_ai_cmds[] = {
    { "Forward", false, NULL, CMD_PROT(ai_forward), 7 },
    { "Right", false, NULL, CMD_PROT(ai_right), 7 },
    { "Left", false, NULL, CMD_PROT(ai_left), 7 },
    { "Look", false, NULL, CMD_PROT(ai_look), 7 },
    { "Inventory", false, NULL, CMD_PROT(ai_inventory), 1 },
    { "Broadcast", true, NULL, CMD_PROT(ai_broadcast), 7 },
    { "Connect_nbr", false, NULL, CMD_PROT(ai_connect_nbr), 0 },
    { "Fork", false, CMD_PROT(ai_pre_fork), CMD_PROT(ai_fork), 42 },
    { "Eject", false, NULL, CMD_PROT(ai_eject), 7 },
    { "Take", true, NULL, CMD_PROT(ai_take), 7 },
    { "Set", true, NULL, CMD_PROT(ai_set), 7 },
    { "Incantation", false, CMD_PROT(ai_pre_incantation),
        CMD_PROT(ai_incantation), 300 },
    { "Cheat_infinite_resources", false, NULL,
        CMD_PROT(ai_cheat_infinite_resources), 0 },
    { "Cheat_level_up", false, NULL, CMD_PROT(ai_cheat_level_up), 0 },
    { "Cheat_teleportation", true, NULL, CMD_PROT(ai_cheat_teleportation), 0 },
    { "", false, NULL, NULL, 0 },
};

void store_cmd_ai(zappy_client_t *client, const char *line)
{
    char *line_copy;

    if (client->ai->commands.commands_queue->size >= 10)
        return;
    line_copy = strdup(line);
    if (!line_copy)
        return;
    list_add(client->ai->commands.commands_queue, line_copy);
}

void cmd_ai(zappy_server_t *server, zappy_client_t *client, const char *line)
{
    size_t cmd_len;

    for (size_t k = 0; server_ai_cmds[k].cmd; k++) {
        cmd_len = strlen(server_ai_cmds[k].key);
        if (strncmp(server_ai_cmds[k].key, line, cmd_len))
            continue;
        if (server_ai_cmds[k].required_arguments && line[cmd_len] != ' ')
            break;
        if (!server_ai_cmds[k].required_arguments && line[cmd_len] != '\0')
            break;
        printf("AI command: %lu: '%s'\n", client->ai->id, line);
        if (server_ai_cmds[k].pre_cmd)
            server_ai_cmds[k].pre_cmd(server, client, line);
        server_ai_cmds[k].cmd(server, client, line);
        return;
    }
    zc_send_line(client, AI_KO);
}