/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_client_data
*/

#include "my.h"
#include "struct.h"
#include <sys/ioctl.h>
#include <poll.h>
#include <stdlib.h>

int handle_client_data(poll_manager_t *manager, int index)
{
    char *buffer = NULL;
    int available = 0;
    int nbytes = 0;

    if (ioctl(manager->fds[index].fd, FIONREAD, &available) == -1)
        return (-1);
    if (available == -1)
        return (-1);
    buffer = malloc(sizeof(char) * (available + 1));
    if (buffer == NULL)
        return (-1);
    nbytes = read(manager->fds[index].fd, buffer, available);
    if (nbytes <= 0) {
        free(buffer);
        remove_client(manager, index);
        return (-1);
    }
    buffer[nbytes] = '\0';
    free(buffer);
    return (0);
}
