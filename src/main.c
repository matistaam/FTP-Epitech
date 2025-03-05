/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** main
*/

#include "my.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int help(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport is the port number on which the server socket listens\n");
    printf("\tpath is the path to the home directory for the Anonymous user");
    printf("\n");
    return (0);
}

int main(int ac, char **av)
{
    int server_fd = 0;
    int port = 0;

    if (av == NULL || ac < 2)
        return (84);
    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return (help());
    port = atoi(av[1]);
    if (port <= 0) {
        write(2, "Invalid port number\n", 20);
        return (84);
    }
    server_fd = create_server_socket(port);
    if (server_fd == -1)
        return (84);
    while (1)
        accept_connection(server_fd);
    close(server_fd);
    return (0);
}
