/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** add_new_client
*/

#include "my.h"

void init_client_and_poll_struct(client_t *client, struct pollfd *poll_fd,
    int client_fd, poll_manager_t *manager)
{
    client->fd = client_fd;
    client->data_fd = -1;
    client->username = NULL;
    client->is_authenticated = false;
    client->current_directory = strdup(manager->root_path);
    client->previous_directory = strdup(manager->root_path);
    poll_fd->fd = client_fd;
    poll_fd->events = POLLIN;
    poll_fd->revents = 0;
}

int resize_poll_fds(poll_manager_t *manager)
{
    size_t new_capacity = manager->capacity + 1;
    struct pollfd *new_fds = NULL;
    client_t *new_clients = NULL;

    new_fds = realloc(manager->fds, sizeof(struct pollfd) * new_capacity);
    new_clients = realloc(manager->clients, sizeof(client_t) * new_capacity);
    if (new_fds == NULL || new_clients == NULL) {
        free(new_fds);
        free(new_clients);
        return (-1);
    }
    manager->fds = new_fds;
    manager->clients = new_clients;
    manager->capacity = new_capacity;
    return (0);
}

int add_new_client(poll_manager_t *manager, int server_fd)
{
    struct sockaddr_in client_addr = {0};
    socklen_t client_len = sizeof(client_addr);
    int client_fd = 0;

    if (resize_poll_fds(manager) == -1)
        return (-1);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
    &client_len);
    if (client_fd == -1)
        return (-1);
    init_client_and_poll_struct(&manager->clients[manager->nfds],
    &manager->fds[manager->nfds], client_fd, manager);
    manager->nfds++;
    printf("Connection from %s:%d\n", inet_ntoa(client_addr.sin_addr),
    ntohs(client_addr.sin_port));
    dprintf(client_fd, "220 Service ready for new user.\r\n");
    return (0);
}
