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

void cleanup_and_notify(poll_manager_t *manager)
{
    for (size_t i = 1; i < manager->nfds; i++)
    dprintf(manager->fds[i].fd, "Service closing control connection.\r\n");
    cleanup_manager(manager);
}

int accept_connection(int server_fd)
{
    poll_manager_t *manager = init_poll_fds(server_fd);
    int status;

    if (manager == NULL)
        return (-1);
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    while (1) {
        status = handle_poll_result(manager,
            poll(manager->fds, manager->nfds, -1), server_fd);
        if (status < 0)
            break;
        if (status == 1)
            continue;
    }
    cleanup_and_notify(manager);
    return (0);
}
