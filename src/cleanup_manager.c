/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** cleanup_manager
*/

#include "my.h"

void cleanup_client(client_t *client)
{
    if (client == NULL)
        return;
    if (client->username != NULL)
        free(client->username);
    if (client->current_directory != NULL)
        free(client->current_directory);
    if (client->data_fd > 0)
        close(client->data_fd);
}

void cleanup_all_clients(poll_manager_t *manager)
{
    if (manager == NULL || manager->clients == NULL)
        return;
    for (size_t i = 1; i < manager->nfds; i++) {
        if (manager->fds != NULL && manager->fds[i].fd > 0)
            close(manager->fds[i].fd);
        cleanup_client(&manager->clients[i]);
    }
}

void cleanup_manager(poll_manager_t *manager)
{
    if (manager == NULL)
        return;
    cleanup_all_clients(manager);
    if (manager->fds != NULL)
        free(manager->fds);
    if (manager->clients != NULL)
        free(manager->clients);
    if (manager->root_path != NULL)
        free(manager->root_path);
    free(manager);
}
