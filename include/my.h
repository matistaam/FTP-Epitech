/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_
    #include "struct.h"
    #include <netinet/in.h>

// File : accept_connection.c
void remove_client(poll_manager_t *manager, int index);
int add_new_client(poll_manager_t *manager, int server_fd);
int handle_poll_events(poll_manager_t *manager, int server_fd);
poll_manager_t *init_poll_fds(int server_fd);
int accept_connection(int server_fd);

// File : create_server_socket.c
int listen_socket(int sock_fd);
int bind_socket(int sock_fd, struct sockaddr_in *server_addr);
int create_socket(void);
int create_server_socket(int port);

// File : handle_client_data.c
int handle_client_data(poll_manager_t *manager, int index);

// File : main.c
int help(void);
int run_server(int port, char *path);
int check_args(int ac, char **av, int *port, char **path);
int main(int ac, char **av);

#endif /* !MY_H_ */
