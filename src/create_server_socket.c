/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** create_server_socket
*/

#include "my.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int accept_connection(int server_fd)
{
    return (0);
}

int listen_socket(int sock_fd)
{
    if (listen(sock_fd, SOMAXCONN) < 0) {
        perror("listen");
        return (-1);
    }
    return (0);
}

int bind_socket(int sock_fd, struct sockaddr_in *server_addr)
{
    if (bind(sock_fd, (struct sockaddr *)server_addr, sizeof(*server_addr))
    < 0) {
        perror("bind");
        return (-1);
    }
    return (0);
}

int create_socket(void)
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd == -1) {
        perror("socket");
        return (-1);
    }
    return (sock_fd);
}

int create_server_socket(void)
{
    int sock_fd = create_socket();
    struct sockaddr_in server_addr;

    if (sock_fd == -1)
        return (-1);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind_socket(sock_fd, &server_addr) == -1)
        return (-1);
    if (listen_socket(sock_fd) == -1)
        return (-1);
    return (sock_fd);
}
