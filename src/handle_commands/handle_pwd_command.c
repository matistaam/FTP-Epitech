/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_pwd_command
*/

#include "my.h"

char *get_relative_path(const char *root, const char *current)
{
    char *root_real = realpath(root, NULL);
    char *current_real = realpath(current, NULL);
    char *relative_path = NULL;

    if (!root_real || !current_real) {
        free(root_real);
        free(current_real);
        return (NULL);
    }
    if (strncmp(current_real, root_real, strlen(root_real)) == 0) {
        relative_path = current_real + strlen(root_real);
        if (!*relative_path || *relative_path != '/')
            relative_path = "/";
    }
    free(root_real);
    free(current_real);
    return (strdup(relative_path));
}

int handle_pwd_command(client_t *client, poll_manager_t *manager)
{
    char *relative_path = get_relative_path(manager->root_path,
    client->current_directory);

    if (!relative_path) {
        dprintf(client->fd, "550 Failed to get current directory.\r\n");
        return (0);
    }
    dprintf(client->fd, "257 \"%s\" is current directory.\r\n", relative_path);
    free(relative_path);
    return (0);
}
