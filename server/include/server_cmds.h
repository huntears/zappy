/*
** EPITECH PROJECT, 2021
** SERVER_CMDS
** File description:
** SERVER_cmds header
*/

#ifndef SERVER_CMDS_H_
#define SERVER_CMDS_H_

#include "zappy_server.h"

#define AI_OK "ok"
#define AI_KO "ko"

#define GUI_KO "sub"
#define GUI_KO_ARGS "sbp"

// zappy callbacks
ns_status_e on_client_connect(
    zappy_server_t *zappy_server, zappy_client_t *zappy_client);
ns_status_e on_client_recv_line(zappy_server_t *zappy_server,
    zappy_client_t *zappy_client, const char *line);
ns_status_e on_client_disconnect(
    zappy_server_t *zappy_server, zappy_client_t *zappy_client);
void on_server_timeval(zappy_server_t *zappy_server);

// command callbacks
#define CMD_PROT(name)                                                         \
    (void (*)(zappy_server_t *, zappy_client_t *, const char *)) cmd_##name

#define ADD_CMD_PROT(name)                                                     \
    void cmd_##name(zappy_server_t *zappy_server,                              \
        zappy_client_t *zappy_client, const char *line)

struct server_ai_cmd {
    char key[64];
    bool required_arguments;
    void (*pre_cmd)(zappy_server_t *, zappy_client_t *, const char *);
    void (*cmd)(zappy_server_t *, zappy_client_t *, const char *);
    size_t time_limit;
};

struct server_gui_cmd {
    char key[64];
    bool required_arguments;
    void (*cmd)(zappy_server_t *, zappy_client_t *, const char *);
};

// client connection
bool client_chose_team(
    zappy_server_t *server, zappy_client_t *client, const char *line);

extern const struct server_ai_cmd server_ai_cmds[];
extern const struct server_gui_cmd server_gui_cmds[];

// main callbacks
ADD_CMD_PROT(ai);
ADD_CMD_PROT(gui);

// AI
// movements
ADD_CMD_PROT(ai_forward);
ADD_CMD_PROT(ai_left);
ADD_CMD_PROT(ai_right);

// infos
ADD_CMD_PROT(ai_look);
ADD_CMD_PROT(ai_inventory);
ADD_CMD_PROT(ai_broadcast);

// actions
ADD_CMD_PROT(ai_connect_nbr);
ADD_CMD_PROT(ai_fork);
ADD_CMD_PROT(ai_pre_fork);
ADD_CMD_PROT(ai_eject);

// objects and incantation
ADD_CMD_PROT(ai_take);
ADD_CMD_PROT(ai_set);
ADD_CMD_PROT(ai_incantation);
ADD_CMD_PROT(ai_pre_incantation);

// cheats
ADD_CMD_PROT(ai_cheat_teleportation);
ADD_CMD_PROT(ai_cheat_level_up);
ADD_CMD_PROT(ai_cheat_infinite_resources);

// GRAPHIC
ADD_CMD_PROT(gui_msz);
ADD_CMD_PROT(gui_bct);
ADD_CMD_PROT(gui_mct);
ADD_CMD_PROT(gui_tna);
ADD_CMD_PROT(gui_ppo);
ADD_CMD_PROT(gui_plv);
ADD_CMD_PROT(gui_pin);
ADD_CMD_PROT(gui_sgt);
ADD_CMD_PROT(gui_sst);

// GRAPHIC replies
void send_gui_bct(zappy_server_t *server, int x, int y);
void send_gui_pnw(zappy_server_t *server, zappy_client_t *client);
void send_gui_ppo(zappy_server_t *server, zappy_client_t *client);
void send_gui_plv(zappy_server_t *server, zappy_client_t *client);
void send_gui_pin(zappy_server_t *server, zappy_client_t *client);
void send_gui_pex(zappy_server_t *server, uint64_t player_id);
void send_gui_pbc(zappy_server_t *server, uint64_t player_id, const char *msg);
void send_gui_pic(zappy_server_t *server, zappy_client_t *client);
void send_gui_pie(zappy_server_t *server, int x, int y, bool result);
void send_gui_pfk(zappy_server_t *server, uint64_t player_id);
void send_gui_pdr(zappy_server_t *server, uint64_t player_id, int object_type);
void send_gui_pgt(zappy_server_t *server, uint64_t player_id, int object_type);
void send_gui_pdi(zappy_server_t *server, uint64_t player_id);
void send_gui_enw(zappy_server_t *server, egg_t *egg);
void send_gui_eht(zappy_server_t *server, uint64_t egg_id);
void send_gui_ebo(zappy_server_t *server, uint64_t egg_id);
void send_gui_edi(zappy_server_t *server, uint64_t egg_id);
void send_gui_sst(zappy_server_t *server, uint64_t frequency);
void send_gui_seg(zappy_server_t *server, const char *winning_team_name);
void send_gui_smg(zappy_server_t *server, const char *server_msg);

void send_gui_bct_to(zappy_client_t *gui, zappy_server_t *server, int x, int y);
void send_gui_pin_to(zappy_client_t *gui, zappy_client_t *client);
void send_gui_plv_to(zappy_client_t *gui, zappy_client_t *client);
void send_gui_ppo_to(zappy_client_t *gui, zappy_client_t *client);
void send_gui_pnw_to(zappy_client_t *gui, zappy_client_t *client);
void send_gui_pnw_to(zappy_client_t *gui, zappy_client_t *client);
void send_gui_pfk_to(zappy_client_t *gui, uint64_t player_id);
void send_gui_eht_to(zappy_client_t *gui, uint64_t egg_id);
void send_gui_enw_to(zappy_client_t *gui, egg_t *egg);

#endif /* !SERVER_CMDS_H_ */