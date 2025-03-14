/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_dele_command
*/

#include "my.h"

int handle_dele_command(poll_manager_t *manager, client_t *client, char *path)
{
    char *full_path = NULL;

    if (path == NULL) {
        dprintf(client->fd, "501 Syntax error in parameters.\r\n");
        return (1);
    }
    full_path = get_path(manager, client, path);
    if (full_path == NULL) {
        dprintf(client->fd, "550 Failed to access file.\r\n");
        return (1);
    }
    if (remove(full_path) == -1) {
        free(full_path);
        dprintf(client->fd, "550 Failed to delete file.\r\n");
        return (1);
    }
    free(full_path);
    dprintf(client->fd, "250 Requested file action okay, completed.\r\n");
    return (0);
}
