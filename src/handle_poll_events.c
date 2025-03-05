/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_poll_events
*/

#include "my.h"

int resize_poll_fds(poll_manager_t *manager)
{
    size_t new_capacity = manager->capacity + 1;
    struct pollfd *new_fds = NULL;
    client_t *new_clients = NULL;

    if (manager == NULL)
        return (-1);
    new_fds = realloc(manager->fds, sizeof(struct pollfd) * new_capacity);
    new_clients = realloc(manager->clients, sizeof(client_t) * new_capacity);
    if (new_fds == NULL || new_clients == NULL) {
        free(new_fds);
        free(new_clients);
        perror("realloc");
        return (-1);
    }
    manager->fds = new_fds;
    manager->clients = new_clients;
    manager->capacity = new_capacity;
    return (0);
}

int handle_events(poll_manager_t *manager, size_t i, int server_fd)
{
    if (i == 0)
        return (add_new_client(manager, server_fd));
    return (handle_client_data(manager, i));
}

int handle_poll_events(poll_manager_t *manager, int server_fd)
{
    int ret = 0;

    for (size_t i = 0; i < manager->nfds; i++) {
        if ((manager->fds[i].revents & POLLIN) == 0)
            continue;
        ret = handle_events(manager, i, server_fd);
        if (ret == -1)
            return (-1);
    }
    return (0);
}

int handle_poll_result(poll_manager_t *manager, int poll_count, int server_fd)
{
    if (poll_count == -1) {
        if (errno == EINTR)
        return (1);
        perror("poll");
        return (-1);
    }
    return (handle_poll_events(manager, server_fd));
}

poll_manager_t *init_poll_fds(int server_fd)
{
    poll_manager_t *manager = malloc(sizeof(poll_manager_t));

    if (manager == NULL)
        return (NULL);
    manager->nfds = 1;
    manager->capacity = 1;
    manager->fds = malloc(sizeof(struct pollfd) * manager->capacity);
    manager->clients = malloc(sizeof(client_t) * manager->capacity);
    if (manager->fds == NULL || manager->clients == NULL) {
        free(manager->fds);
        free(manager->clients);
        free(manager);
        return (NULL);
    }
    memset(manager->fds, 0, sizeof(struct pollfd) * manager->capacity);
    memset(manager->clients, 0, sizeof(client_t) * manager->capacity);
    manager->fds[0].fd = server_fd;
    manager->fds[0].events = POLLIN;
    return (manager);
}
