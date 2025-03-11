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

int check_args(int ac, char **av, int *port)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return (help());
    if (ac != 3) {
        write(2, "Invalid number of arguments\n", 28);
        return (-1);
    }
    *port = atoi(av[1]);
    if (*port <= 0) {
        write(2, "Invalid port number\n", 20);
        return (-1);
    }
    if (access(av[2], F_OK | R_OK) == -1) {
        write(2, "Invalid path\n", 13);
        return (-1);
    }
    return (0);
}

int handle_server(poll_manager_t *manager, int server_fd)
{
    int ret = accept_connection(manager);

    cleanup_manager(manager);
    close(server_fd);
    if (ret == -1)
        return (84);
    return (0);
}

int main(int ac, char **av)
{
    int server_fd = 0;
    int port = 0;
    int ret = 0;
    poll_manager_t *manager = NULL;

    ret = check_args(ac, av, &port);
    if (ret == -1)
        return (84);
    server_fd = create_server_socket(port);
    if (server_fd == -1) {
        close(server_fd);
        return (84);
    }
    manager = init_poll_fds(server_fd, av[2]);
    if (manager == NULL) {
        close(server_fd);
        return (84);
    }
    return (handle_server(manager, server_fd));
}
