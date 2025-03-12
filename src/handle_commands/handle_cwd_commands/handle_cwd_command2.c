/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_cwd_command2
*/

#include "my.h"

int is_path_allowed(const char *root, const char *path)
{
    char *root_realpath = realpath(root, NULL);
    char *path_realpath = realpath(path, NULL);
    int allowed = 0;

    if (!root_realpath || !path_realpath) {
        free(root_realpath);
        free(path_realpath);
        return (0);
    }
    allowed = strncmp(path_realpath, root_realpath,
    strlen(root_realpath)) == 0;
    free(root_realpath);
    free(path_realpath);
    return (allowed);
}

char *resolve_directory_path(char *path)
{
    char *resolved = realpath(path, NULL);

    free(path);
    return (resolved);
}

int check_directory_access(const char *path, int client_fd)
{
    if (access(path, F_OK | R_OK) == -1) {
        dprintf(client_fd, "550 Failed to change directory.\r\n");
        return (0);
    }
    return (1);
}

int handle_previous_directory(client_t *client)
{
    char *new_path = NULL;

    if (client->previous_directory == NULL) {
        dprintf(client->fd, "550 No previous directory.\r\n");
        return (0);
    }
    new_path = strdup(client->previous_directory);
    if (new_path == NULL) {
        dprintf(client->fd, "550 Memory allocation failed.\r\n");
        return (0);
    }
    if (!check_directory_access(new_path, client->fd)) {
        free(new_path);
        return (0);
    }
    return (update_directories(client, new_path));
}
