/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_pasv_command
*/

#include "my.h"

int accept_pasv_connection(client_t *client, int pasv_sock)
{
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    int port;

    if (getsockname(pasv_sock, (struct sockaddr *)&addr, &addr_len) == -1) {
        close(pasv_sock);
        return (-1);
    }
    port = ntohs(addr.sin_port);
    dprintf(client->fd, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n",
    127, 0, 0, 1, port >> 8, port & 0xff);
    client->data_fd = accept(pasv_sock, NULL, NULL);
    close(pasv_sock);
    return (client->data_fd);
}

int create_pasv_socket(void)
{
    int sock_fd = create_socket();
    struct sockaddr_in addr;

    if (sock_fd == -1)
        return (-1);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(0);
    if (bind_socket(sock_fd, &addr) == -1)
        return (-1);
    if (listen_socket(sock_fd) == -1)
        return (-1);
    return (sock_fd);
}

int handle_pasv_command(client_t *client)
{
    int pasv_sock = create_pasv_socket();

    if (pasv_sock == -1) {
        dprintf(client->fd, "425 Can't open passive connection.\r\n");
        return (0);
    }
    if (accept_pasv_connection(client, pasv_sock) == -1) {
        dprintf(client->fd, "425 Can't open passive connection.\r\n");
        return (0);
    }
    return (0);
}
