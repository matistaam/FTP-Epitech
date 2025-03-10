/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_cdup_command
*/

#include "my.h"

int handle_cdup_command(client_t *client)
{
    char *parent_dir = NULL;
    char *last_slash = NULL;

    if (client->current_directory == NULL ||
    strcmp(client->current_directory, "/") == 0) {
        dprintf(client->fd, "200 Command okay.\r\n");
        return (0);
    }
    last_slash = strrchr(client->current_directory, '/');
    if (last_slash == client->current_directory) {
        free(client->current_directory);
        client->current_directory = strdup("/");
    } else {
        *last_slash = '\0';
        parent_dir = strdup(client->current_directory);
        free(client->current_directory);
        client->current_directory = parent_dir;
    }
    dprintf(client->fd, "200 Command okay.\r\n");
    return (0);
}
