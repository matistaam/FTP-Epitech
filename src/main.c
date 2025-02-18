/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** main
*/

#include "my.h"
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

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

    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return (help());
    server_fd = create_server_socket();
    if (server_fd == -1)
        return (84);
    accept_connection(server_fd);
    close(server_fd);
    return (0);
}
