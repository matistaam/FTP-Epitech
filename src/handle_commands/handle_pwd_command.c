/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_pwd_command
*/

#include "my.h"

int handle_pwd_command(poll_manager_t *manager, client_t *client)
{
    char *current_real = realpath(client->current_directory, NULL);
    char *root_real = realpath(manager->root_path, NULL);
    char *relative_path = NULL;

    if (current_real == NULL || root_real == NULL) {
        if (current_real != NULL)
            free(current_real);
        if (root_real != NULL)
            free(root_real);
        dprintf(client->fd, "550 Failed to get current directory.\r\n");
        return (1);
    }
    relative_path = current_real + strlen(root_real);
    if (!*relative_path || *relative_path != '/')
        relative_path = "/";
    dprintf(client->fd, "257 \"%s\" is current directory.\r\n", relative_path);
    free(current_real);
    free(root_real);
    return (0);
}
