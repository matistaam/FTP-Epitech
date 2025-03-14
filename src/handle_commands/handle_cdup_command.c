/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_cdup_command
*/

#include "my.h"

int handle_cdup_command(poll_manager_t *manager, client_t *client)
{
    char *new_path = NULL;
    struct stat st = {0};

    new_path = get_path(manager, client, "..");
    if (new_path == NULL) {
        dprintf(client->fd, "550 Failed to access parent directory.\r\n");
        return (1);
    }
    if (stat(new_path, &st) == -1 || !S_ISDIR(st.st_mode) ||
        access(new_path, R_OK | X_OK) == -1) {
        dprintf(client->fd, "550 Failed to access directory.\r\n");
        free(new_path);
        return (1);
    }
    if (update_directories(client, new_path) == 0)
        dprintf(client->fd, "200 Directory successfully changed.\r\n");
    return (0);
}
