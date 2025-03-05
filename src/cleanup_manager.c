/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** cleanup_manager
*/

#include "my.h"

void cleanup_manager(poll_manager_t *manager)
{
    if (manager == NULL)
        return;
    for (size_t i = 1; i < manager->nfds; i++) {
        if (manager->fds[i].fd > 0)
            close(manager->fds[i].fd);
        free(manager->clients[i].username);
    }
    free(manager->fds);
    free(manager->clients);
    free(manager);
}
