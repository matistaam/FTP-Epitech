/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_client_data
*/

#include "my.h"

int check_available_data(poll_manager_t *manager, int index, int *available)
{
    if (ioctl(manager->fds[index].fd, FIONREAD, available) == -1) {
        perror("ioctl");
        remove_client(manager, index);
        return (-1);
    }
    if (*available <= 0) {
        remove_client(manager, index);
        return (-1);
    }
    return (0);
}

char *read_client_data(poll_manager_t *manager, int index, int available,
    int *nbytes)
{
    char *buffer = malloc(sizeof(char) * (available + 1));

    if (buffer == NULL)
        return (NULL);
    *nbytes = read(manager->fds[index].fd, buffer, available);
    if (*nbytes == -1) {
        free(buffer);
        remove_client(manager, index);
        return (NULL);
    }
    buffer[*nbytes] = '\0';
    return (buffer);
}

int handle_client_data(poll_manager_t *manager, int index)
{
    int available = 0;
    int nbytes = 0;
    char *buffer = NULL;
    int ret = 0;

    if (check_available_data(manager, index, &available) == -1)
        return (-1);
    buffer = read_client_data(manager, index, available, &nbytes);
    if (buffer == NULL)
        return (-1);
    ret = parse_ftp_command(&manager->clients[index], buffer);
    free(buffer);
    if (ret == -1)
        remove_client(manager, index);
    return (ret);
}
