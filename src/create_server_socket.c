/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** create_server_socket
*/

#include "my.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

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
    write(client_fd, "I lost the game :3\n", strlen("I lost the game :3\n"));
    close(client_fd);
    return (0);
}

int listen_socket(int sock_fd)
{
    if (listen(sock_fd, SOMAXCONN) < 0) {
        perror("listen");
        close(sock_fd);
        return (-1);
    }
    return (0);
}

int bind_socket(int sock_fd, struct sockaddr_in *server_addr)
{
    if (bind(sock_fd, (struct sockaddr *)server_addr, sizeof(*server_addr))
    < 0) {
        perror("bind");
        close(sock_fd);
        return (-1);
    }
    return (0);
}

int create_socket(void)
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd == -1) {
        perror("socket");
        close(sock_fd);
        return (-1);
    }
    return (sock_fd);
}

int create_server_socket(int port)
{
    int sock_fd = create_socket();
    struct sockaddr_in server_addr;

    if (sock_fd == -1)
        return (-1);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind_socket(sock_fd, &server_addr) == -1)
        return (-1);
    if (listen_socket(sock_fd) == -1)
        return (-1);
    return (sock_fd);
}
