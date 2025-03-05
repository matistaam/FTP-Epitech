/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** main
*/

#include "my.h"

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
    int ret = 0;

    if (ac != 2)
        return (84);
    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return (help());
    port = atoi(av[1]);
    if (port <= 0)
        return (84);
    server_fd = create_server_socket(port);
    if (server_fd == -1)
        return (84);
    ret = accept_connection(server_fd);
    close(server_fd);
    if (ret == -1)
        return (84);
    return (0);
}
