/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_
    #include "struct.h"
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <poll.h>
    #include <sys/ioctl.h>
    #include <signal.h>
    #include <errno.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <time.h>

/* handle_commands */
// File : handle_cdup_command.c
int check_cdup_args(client_t *client, char *path);
int is_root_directory(client_t *client, poll_manager_t *manager);
int handle_cdup_command(client_t *client, char *path, poll_manager_t *manager);

// File : handle_cwd_commands/handle_cwd_command.c
int update_directories(client_t *client, char *new_path);
int handle_path_resolution(client_t *client, char *temp_path, char **new_path,
    poll_manager_t *manager);
char *build_path(const char *current_dir, const char *new_path,
    poll_manager_t *manager);
int handle_directory_change(client_t *client, char *path,
    poll_manager_t *manager);
int handle_cwd_command(client_t *client, char *path, poll_manager_t *manager);

// File : handle_cwd_commands/handle_cwd_command2.c
int is_path_allowed(const char *root, const char *path);
char *resolve_directory_path(char *path);
int check_directory_access(const char *path, int client_fd);
int handle_previous_directory(client_t *client);

// File : handle_dele_command.c
int handle_dele_command(client_t *client, char *path);

// File : handle_help_command.c
int handle_help_command(client_t *client);

// File : handle_list_commands/handle_list_command.c
void cleanup_and_close(client_t *client, DIR *dir, char *target_path,
    char *path);
void list_directory_content(int data_fd, DIR *dir, const char *base_path);
int check_data_connection(client_t *client);
char *get_target_path(client_t *client, char *path, poll_manager_t *manager);
int handle_list_command(client_t *client, char *path, poll_manager_t *manager);

// File : handle_list_commands/handle_list_command2.c
char *get_base_path(client_t *client, char *path, poll_manager_t *manager);

// File : handle_noop_command.c
int handle_noop_command(client_t *client);

// File : handle_pass_command.c
int handle_pass_command(client_t *client, char *command);

// File : handle_pasv_command.c
int accept_pasv_connection(client_t *client, int pasv_sock);
int create_pasv_socket(void);
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
int accept_connection(poll_manager_t *manager);

// File : add_new_client.c
void init_client_and_poll_struct(client_t *client, struct pollfd *poll_fd,
    int client_fd, poll_manager_t *manager);
int resize_poll_fds(poll_manager_t *manager);
int add_new_client(poll_manager_t *manager, int server_fd);

// File : cleanup_manager.c
void cleanup_client(client_t *client);
void cleanup_all_clients(poll_manager_t *manager);
void cleanup_manager(poll_manager_t *manager);

// File : create_server_socket.c
int listen_socket(int sock_fd);
int bind_socket(int sock_fd, struct sockaddr_in *server_addr);
int create_socket(void);
int create_server_socket(int port);

// File : handle_client_data.c
void remove_client(poll_manager_t *manager, int index);
char *read_client_data(poll_manager_t *manager, int index, int available,
    int *nbytes);
int check_available_data(poll_manager_t *manager, int index, int *available);
int handle_client_data(poll_manager_t *manager, int index);

// File : handle_poll_events.c
int handle_events(poll_manager_t *manager, size_t i, int server_fd);
int handle_poll_events(poll_manager_t *manager, int server_fd);
int handle_poll_result(poll_manager_t *manager, int poll_count, int server_fd);
poll_manager_t *init_poll_fds(int server_fd, const char *root_path);

// File : main.c
int help(void);
int check_args(int ac, char **av, int *port);
int handle_server(poll_manager_t *manager, int server_fd);
int main(int ac, char **av);

// File : parse_ftp_command.c
int execute_command2(client_t *client, const char *command, char *args,
    poll_manager_t *manager);
int execute_command(client_t *client, const char *command, char *args,
    poll_manager_t *manager);
int check_authentication(client_t *client, const char *command);
int parse_ftp_command(client_t *client, char *buffer, poll_manager_t *manager);

#endif /* !MY_H_ */
