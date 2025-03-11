/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** struct
*/

#ifndef STRUCT_H_
    #define STRUCT_H_
    #include "my.h"
    #include "unistd.h"
    #include "stdbool.h"

typedef struct client_s {
    int fd;
    int data_fd;
    char *username;
    bool is_authenticated;
    char *current_directory;
} client_t;

typedef struct poll_manager_s {
    struct pollfd *fds;
    client_t *clients;
    size_t nfds;
    size_t capacity;
    char *root_path;
} poll_manager_t;

#endif /* !STRUCT_H_ */
