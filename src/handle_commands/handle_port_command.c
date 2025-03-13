/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_port_command
*/

#include "my.h"

int create_data_socket(client_t *client, struct sockaddr_in *addr)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        dprintf(client->fd, "425 Can't open data connection.\r\n");
        return (-1);
    }
    if (connect(sock, (struct sockaddr *)addr, sizeof(*addr)) == -1) {
        close(sock);
        dprintf(client->fd, "425 Can't open data connection.\r\n");
        return (-1);
    }
    return (sock);
}

void configure_addr(struct sockaddr_in *addr, int *values)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(values[4] * 256 + values[5]);
    addr->sin_addr.s_addr = htonl((values[0] << 24) | (values[1] << 16) |
    (values[2] << 8) | values[3]);
}

int parse_values(char *str, int *values)
{
    char *token = strtok(str, ",");
    int i = 0;

    while (token && i < 6) {
        values[i] = atoi(token);
        if (values[i] < 0 || values[i] > 255)
            return (0);
        token = strtok(NULL, ",");
        i++;
    }
    return (i == 6);
}

int parse_port_args(const char *args, struct sockaddr_in *addr)
{
    int values[6] = {0};
    char *str = strdup(args);
    int ret = 0;

    if (!str)
        return (0);
    ret = parse_values(str, values);
    free(str);
    if (!ret)
        return (0);
    configure_addr(addr, values);
    return (1);
}

int handle_port_command(client_t *client, char *args)
{
    struct sockaddr_in addr;

    if (!args) {
        dprintf(client->fd, "501 Syntax error in parameters.\r\n");
        return (0);
    }
    if (client->data_fd != -1) {
        close(client->data_fd);
        client->data_fd = -1;
    }
    if (!parse_port_args(args, &addr)) {
        dprintf(client->fd, "501 Syntax error in parameters.\r\n");
        return (0);
    }
    client->data_fd = create_data_socket(client, &addr);
    if (client->data_fd == -1)
        return (0);
    dprintf(client->fd, "200 Command okay.\r\n");
    return (0);
}
