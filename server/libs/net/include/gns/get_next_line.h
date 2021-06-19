/*
** EPITECH PROJECT, 2021
** GET_NEXT_LINE
** File description:
** Get_next_line header
*/

#ifndef GET_NEXT_LINE_H_
#define GET_NEXT_LINE_H_

#ifndef EOT
#define EOT (4)
#endif /* EOT */

/// PROTOTYPES

char *gnl(int socket_fd, int *read_len);
char *gnl_extract_next_line(int socket_fd);

#endif /* !GET_NEXT_LINE_H_ */