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

int run_server(int server_fd)
{
    int ret = accept_connection(server_fd);

    close(server_fd);
    if (ret == -1) {
        write(2, "Error while accepting connection\n", 33);
        return (84);
    }
    return (0);
}

int check_args(int ac, char **av, int *port)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return (help());
    if (ac != 3) {
        write(2, "Invalid number of arguments\n", 28);
        return (84);
    }
    *port = atoi(av[1]);
    if (*port <= 0) {
        write(2, "Invalid port number\n", 20);
        return (84);
    }
    if (access(av[2], F_OK | R_OK) == -1) {
        write(2, "Invalid path\n", 13);
        return (84);
    }
    return (0);
}

int main(int ac, char **av)
{
    int server_fd = 0;
    int port = 0;
    int ret = 0;

    ret = check_args(ac, av, &port);
    if (ret != 0)
        return (ret);
    server_fd = create_server_socket(port);
    if (server_fd == -1)
        return (84);
    return (run_server(server_fd));
}
