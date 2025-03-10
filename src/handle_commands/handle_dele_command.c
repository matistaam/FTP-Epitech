/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_dele_command
*/

#include "my.h"

int handle_dele_command(client_t *client, char *path)
{
    if (path == NULL) {
        dprintf(client->fd, "501 Syntax error in parameters.\r\n");
        return (0);
    }
    if (access(path, F_OK | W_OK) == -1) {
        dprintf(client->fd, "550 Failed to delete file.\r\n");
        return (0);
    }
    if (remove(path) == -1) {
        dprintf(client->fd, "550 Failed to delete file.\r\n");
        return (0);
    }
    dprintf(client->fd, "250 Requested file action okay, completed.\r\n");
    return (0);
}
