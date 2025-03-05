/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** accept_connection
*/

#include "my.h"

void cleanup_manager(poll_manager_t *manager)
{
    if (!manager)
        return;
    for (size_t i = 1; i < manager->nfds; i++)
        close(manager->fds[i].fd);
    free(manager->fds);
    free(manager);
}

int resize_poll_fds(poll_manager_t *manager)
{
    size_t new_capacity = manager->capacity + 1;
    struct pollfd *new_fds = realloc(manager->fds, sizeof(struct pollfd) *
    new_capacity);

    if (new_fds == NULL)
        return (-1);
    manager->fds = new_fds;
    manager->capacity = new_capacity;
    return (0);
}

int handle_poll_events(poll_manager_t *manager, int server_fd)
{
    for (size_t i = 0; i < manager->nfds; i++) {
        if (!(manager->fds[i].revents & POLLIN))
            continue;
        if (i != 0)
            return (handle_client_data(manager, i));
        if (add_new_client(manager, server_fd) == -1)
            continue;
    }
    return (0);
}

poll_manager_t *init_poll_fds(int server_fd)
{
    poll_manager_t *manager = malloc(sizeof(poll_manager_t));

    if (manager == NULL)
        return (NULL);
    manager->nfds = 1;
    manager->capacity = 1;
    manager->fds = malloc(sizeof(struct pollfd) * manager->capacity);
    if (manager->fds == NULL) {
        free(manager);
        return (NULL);
    }
    manager->fds[0].fd = server_fd;
    manager->fds[0].events = POLLIN;
    return (manager);
}

int accept_connection(int server_fd)
{
    poll_manager_t *manager = init_poll_fds(server_fd);
    int poll_count = 0;

    if (manager == NULL)
        return (-1);
    while (1) {
        poll_count = poll(manager->fds, manager->nfds, -1);
        if (poll_count == -1) {
            perror("poll");
            cleanup_manager(manager);
            return (-1);
        }
        if (handle_poll_events(manager, server_fd) == -1)
            break;
    }
    cleanup_manager(manager);
    return (0);
}
