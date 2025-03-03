/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** accept_connection
*/

#include "my.h"
#include "struct.h"
#include <arpa/inet.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_client(poll_manager_t *manager, int index)
{
    close(manager->fds[index].fd);
    for (size_t i = index; i < manager->nfds - 1; i++)
        manager->fds[i] = manager->fds[i + 1];
    manager->nfds--;
}

int add_new_client(poll_manager_t *manager, int server_fd)
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = 0;

    if (manager->nfds >= manager->capacity)
        return (-1);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
    &client_len);
    if (client_fd == -1)
        return (-1);
    manager->fds[manager->nfds].fd = client_fd;
    manager->fds[manager->nfds].events = POLLIN;
    manager->nfds++;
    printf("Connection from %s:%d\n",
    inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
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
    manager->capacity = 10;
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
            free(manager->fds);
            free(manager);
            return (-1);
        }
        if (handle_poll_events(manager, server_fd) == -1)
            return (-1);
    }
    return (0);
}
