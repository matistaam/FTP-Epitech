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
    #include <arpa/inet.h>
    #include <poll.h>
    #include <sys/ioctl.h>
    #include <signal.h>
    #include <errno.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

/* handle_commands */
// File : handle_cdup_command.c
int handle_cdup_command(client_t *client);

// File : handle_cwd_command.c
int handle_cwd_command(client_t *client, char *path);

// File : handle_dele_command.c
int handle_dele_command(client_t *client, char *path);

// File : handle_help_command.c
int handle_help_command(client_t *client);

// File : handle_list_command.c
int handle_list_command(client_t *client, char *path);

// File : handle_noop_command.c
int handle_noop_command(client_t *client);

// File : handle_pass_command.c
int handle_pass_command(client_t *client, char *command);

// File : handle_pasv_command.c
int handle_pasv_command(client_t *client);

// File : handle_port_command.c
int handle_port_command(client_t *client, char *args);

// File : handle_pwd_command.c
int handle_pwd_command(client_t *client);

// File : handle_quit_command.c
int handle_quit_command(client_t *client);

// File : handle_retr_command.c
int handle_retr_command(client_t *client, char *path);

// File : handle_stor_command.c
int handle_stor_command(client_t *client, char *path);

// File : handle_user_command.c
int handle_user_command(client_t *client, char *command);


/* src */
// File : accept_connection.c
void signal_handler(int signum);
void cleanup_and_notify(poll_manager_t *manager);
int accept_connection(int server_fd);

// File : add_new_client.c
void remove_client(poll_manager_t *manager, int index);
void init_client_and_poll_struct(client_t *client, struct pollfd *poll_fd,
    int client_fd);
int add_new_client(poll_manager_t *manager, int server_fd);

// File : cleanup_manager.c
void cleanup_manager(poll_manager_t *manager);

// File : create_server_socket.c
int listen_socket(int sock_fd);
int bind_socket(int sock_fd, struct sockaddr_in *server_addr);
int create_socket(void);
int create_server_socket(int port);

// File : handle_client_data.c
int check_available_data(poll_manager_t *manager, int index, int *available);
char *read_client_data(poll_manager_t *manager, int index, int available,
    int *nbytes);
int handle_client_data(poll_manager_t *manager, int index);

// File : handle_poll_events.c
int resize_poll_fds(poll_manager_t *manager);
int handle_events(poll_manager_t *manager, size_t i, int server_fd);
int handle_poll_events(poll_manager_t *manager, int server_fd);
int handle_poll_result(poll_manager_t *manager, int poll_count, int server_fd);
poll_manager_t *init_poll_fds(int server_fd);

// File : main.c
int help(void);
int run_server(int server_fd);
int check_args(int ac, char **av, int *port);
int main(int ac, char **av);

// File : parse_ftp_command.c
int check_authentication(client_t *client, const char *command);
int execute_command2(client_t *client, const char *command, char *args);
int execute_command(client_t *client, const char *command, char *args);
int parse_ftp_command(client_t *client, char *buffer);

#endif /* !MY_H_ */
