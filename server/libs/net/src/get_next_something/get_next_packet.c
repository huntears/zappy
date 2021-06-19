/*
** EPITECH PROJECT, 2021
** GET_NEXT_PACKET
** File description:
** Get_next_packet function
*/

#include <stdlib.h>
#include <string.h>

#include "gns/get_next_packet.h"
#include "gns/get_next_something.h"

static struct gnp_pck *try_to_extract_packet(net_buffer_t *buffer)
{
    struct gnp_pck pck_info;

    if (buffer->length < sizeof(struct gnp_pck))
        return NULL;
    memcpy(&pck_info, buffer->buffer, sizeof(struct gnp_pck));
    if (buffer->length < pck_info.payload_length + sizeof(struct gnp_pck))
        return NULL;
    return net_buffer_pop(
        buffer, pck_info.payload_length + sizeof(struct gnp_pck));
}

void *gnp_extract_next_packet(int socket_fd)
{
    gns_buffer_t *buffer = get_gns_buffer(socket_fd);

    if (!buffer)
        return NULL;
    return try_to_extract_packet(&buffer->buffer);
}

void *gnp(int socket_fd, int *read_len)
{
    gns_buffer_t *buffer = get_gns_buffer(socket_fd);
    struct gnp_pck *packet;

    if (!buffer) {
        *read_len = -1;
        return NULL;
    }
    packet = try_to_extract_packet(&buffer->buffer);
    if (packet) {
        *read_len = packet->payload_length + sizeof(struct gnp_pck);
        return packet;
    }
    *read_len = gns(socket_fd);
    if (*read_len <= 0)
        return NULL;
    return try_to_extract_packet(&buffer->buffer);
}