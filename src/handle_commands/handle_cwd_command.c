/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_cwd_command
*/

#include "my.h"

int handle_cwd_command(client_t *client, char *path)
{
    char *new_path = NULL;

    if (path == NULL) {
        dprintf(client->fd, "501 Syntax error in parameters.\r\n");
        return (0);
    }
    if (access(path, F_OK | R_OK) == -1) {
        dprintf(client->fd, "550 Failed to change directory.\r\n");
        return (0);
    }
    new_path = strdup(path);
    if (new_path == NULL) {
        dprintf(client->fd, "550 Failed to change directory.\r\n");
        return (0);
    }
    free(client->current_directory);
    client->current_directory = new_path;
    dprintf(client->fd, "250 Directory successfully changed.\r\n");
    return (0);
}
