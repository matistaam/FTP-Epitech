/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_poll_events
*/

#include "my.h"

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
        return (-1);
    }
    return (handle_poll_events(manager, server_fd));
}

poll_manager_t *init_poll_fds(int server_fd, const char *root_path)
{
    poll_manager_t *manager = malloc(sizeof(poll_manager_t));

    if (manager == NULL)
        return (NULL);
    manager->nfds = 1;
    manager->capacity = 1;
    manager->fds = malloc(sizeof(struct pollfd) * manager->capacity);
    manager->clients = malloc(sizeof(client_t) * manager->capacity);
    manager->root_path = strdup(root_path);
    if (manager->fds == NULL || manager->clients == NULL ||
    manager->root_path == NULL) {
        return (NULL);
    }
    memset(manager->fds, 0, sizeof(struct pollfd) * manager->capacity);
    memset(manager->clients, 0, sizeof(client_t) * manager->capacity);
    manager->fds[0].fd = server_fd;
    manager->fds[0].events = POLLIN;
    return (manager);
}
