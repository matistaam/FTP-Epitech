/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** accept_connection
*/

#include "my.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int handle_fork(int client_fd)
{
    pid_t pid = fork();

    if (pid == 0) {
        write(client_fd, "I lost the game :3\n",
        strlen("I lost the game :3\n"));
        close(client_fd);
        exit(0);
    } else if (pid > 0) {
        close(client_fd);
        return (0);
    } else {
        perror("fork");
        close(client_fd);
        return (-1);
    }
}

int accept_connection(int server_fd)
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
    &client_len);

    if (client_fd < 0) {
        perror("accept");
        close(server_fd);
        return (-1);
    }
    printf("Connection from %s:%d\n", inet_ntoa(client_addr.sin_addr),
    ntohs(client_addr.sin_port));
    return (handle_fork(client_fd));
}
