/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_
    #include <netinet/in.h>

// File : accept_connection.c
int handle_fork(int client_fd);
int accept_connection(int server_fd);

// File : create_server_socket.c
int listen_socket(int sock_fd);
int bind_socket(int sock_fd, struct sockaddr_in *server_addr);
int create_socket(void);
int create_server_socket(int port);

// File : main.c
int help(void);
int run_server(int port, char *path);
int check_args(int ac, char **av, int *port, char **path);
int main(int ac, char **av);

#endif /* !MY_H_ */
