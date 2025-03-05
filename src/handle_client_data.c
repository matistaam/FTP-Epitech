/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_client_data
*/

#include "my.h"

int handle_client_data(poll_manager_t *manager, int index)
{
    char *buffer = NULL;
    int available = 0;
    int nbytes = 0;

    if (ioctl(manager->fds[index].fd, FIONREAD, &available) == -1)
        return (-1);
    if (available == -1)
        return (-1);
    buffer = malloc(sizeof(char) * (available + 1));
    if (buffer == NULL)
        return (-1);
    nbytes = read(manager->fds[index].fd, buffer, available);
    if (nbytes == -1) {
        free(buffer);
        remove_client(manager, index);
        return (-1);
    }
    buffer[nbytes] = '\0';
    free(buffer);
    return (0);
}

void remove_client(poll_manager_t *manager, int index)
{
    close(manager->fds[index].fd);
    for (size_t i = index; i < manager->nfds - 1; i++)
        manager->fds[i] = manager->fds[i + 1];
    manager->nfds--;
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
    manager->fds[manager->nfds].fd = client_fd;
    manager->fds[manager->nfds].events = POLLIN;
    manager->nfds++;
    printf("Connection from %s:%d\n", inet_ntoa(client_addr.sin_addr),
    ntohs(client_addr.sin_port));
    return (0);
}
