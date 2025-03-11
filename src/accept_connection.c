/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** accept_connection
*/

#include "my.h"

void signal_handler(int signum)
{
    (void)signum;
    exit(0);
}

int accept_connection(poll_manager_t *manager)
{
    int status = 0;

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    while (1) {
        status = handle_poll_result(manager,
        poll(manager->fds, manager->nfds, -1), manager->fds[0].fd);
        if (status == -1)
            break;
        if (status == 1)
            continue;
    }
    for (size_t i = 1; i < manager->nfds; i++)
        dprintf(manager->fds[i].fd, "Service closing control connection.\r\n");
    return (0);
}
