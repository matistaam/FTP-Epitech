/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** add_new_client
*/

#include "my.h"

void remove_client(poll_manager_t *manager, int index)
{
    printf("Client disconnected (fd: %d)\n", manager->fds[index].fd);
    close(manager->fds[index].fd);
    free(manager->clients[index].username);
    for (size_t i = index; i < manager->nfds - 1; i++) {
        manager->fds[i] = manager->fds[i + 1];
        manager->clients[i] = manager->clients[i + 1];
    }
    manager->nfds--;
}

void init_client_and_poll_struct(client_t *client, struct pollfd *poll_fd,
    int client_fd)
{
    client->fd = client_fd;
    client->username = NULL;
    client->is_authenticated = false;
    poll_fd->fd = client_fd;
    poll_fd->events = POLLIN;
    poll_fd->revents = 0;
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
    &manager->fds[manager->nfds], client_fd);
    manager->nfds++;
    printf("Connection from %s:%d\n", inet_ntoa(client_addr.sin_addr),
    ntohs(client_addr.sin_port));
    dprintf(client_fd, "220 Service ready for new user.\r\n");
    return (0);
}
