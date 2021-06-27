/*
** EPITECH PROJECT, 2021
** SIGNAL
** File description:
** Signal function
*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include "tools/tools.h"

void signal_handler(int signal)
{
    if (signal == SIGINT)
        printf("SIGINT received\n");
    if (signal == SIGPIPE)
        printf("SIGPIPE received\n");
    if (signal == SIGTERM)
        kill(getpid(), SIGINT);
}