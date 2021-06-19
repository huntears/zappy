/*
** EPITECH PROJECT, 2021
** GET_NEXT_PACKET
** File description:
** Get_next_packet header
*/

#ifndef GET_NEXT_PACKET_H_
#define GET_NEXT_PACKET_H_

#include <stdint.h>

struct gnp_pck {
    uint16_t payload_length;
    uint8_t id;
} __attribute__((__packed__, scalar_storage_order("little-endian")));

/// PROTOTYPES

void *gnp(int socket_fd, int *read_len);
void *gnp_extract_next_packet(int socket_fd);

#endif /* !GET_NEXT_PACKET_H_ */