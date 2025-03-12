/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_cdup_command
*/

#include "my.h"

int check_cdup_args(client_t *client, char *path)
{
    if (path != NULL) {
        dprintf(client->fd, "501 CDUP does not accept arguments.\r\n");
        return (0);
    }
    if (client->current_directory == NULL) {
        dprintf(client->fd, "550 No current directory set.\r\n");
        return (0);
    }
    return (1);
}

int is_root_directory(client_t *client, poll_manager_t *manager)
{
    char *realpath_current = realpath(client->current_directory, NULL);
    char *realpath_root = realpath(manager->root_path, NULL);
    int is_root = 0;

    if (!realpath_current || !realpath_root) {
        free(realpath_current);
        free(realpath_root);
        dprintf(client->fd, "550 Failed to resolve path.\r\n");
        return (-1);
    }
    is_root = (strcmp(realpath_current, realpath_root) == 0);
    free(realpath_current);
    free(realpath_root);
    if (is_root) {
        dprintf(client->fd, "550 Already at root directory.\r\n");
        return (1);
    }
    return (0);
}

int handle_cdup_command(client_t *client, char *path, poll_manager_t *manager)
{
    int root_check;
    int success;

    if (!check_cdup_args(client, path))
        return (0);
    root_check = is_root_directory(client, manager);
    if (root_check != 0)
        return (0);
    success = handle_directory_change(client, "..", manager);
    if (!success)
        return (0);
    dprintf(client->fd, "200 Directory successfully changed.\r\n");
    return (0);
}
