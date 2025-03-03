/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** struct
*/

#ifndef STRUCT_H_
    #define STRUCT_H_
    #include <unistd.h>

typedef struct poll_manager_s {
    struct pollfd *fds;
    size_t nfds;
    size_t capacity;
} poll_manager_t;

#endif /* !STRUCT_H_ */
