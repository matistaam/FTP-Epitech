/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_cwd_command
*/

#include "my.h"

int update_directories(client_t *client, char *new_path)
{
    free(client->previous_directory);
    client->previous_directory = client->current_directory;
    client->current_directory = new_path;
    return (0);
}

int handle_directory_change(poll_manager_t *manager, client_t *client,
    char *path)
{
    char *new_path = get_path(manager, client, path);
    struct stat st = {0};

    if (new_path == NULL) {
        dprintf(client->fd, "550 Failed to change directory.\r\n");
        return (1);
    }
    if (stat(new_path, &st) == -1 || !S_ISDIR(st.st_mode) ||
    access(new_path, R_OK | X_OK) == -1) {
        dprintf(client->fd, "550 Failed to access directory.\r\n");
        free(new_path);
        return (1);
    }
    return (update_directories(client, new_path));
}

int handle_previous_directory(client_t *client)
{
    char *new_path = NULL;
    struct stat st = {0};

    if (client->previous_directory == NULL) {
        dprintf(client->fd, "550 No previous directory.\r\n");
        return (1);
    }
    if (stat(client->previous_directory, &st) == -1 || !S_ISDIR(st.st_mode) ||
    access(client->previous_directory, R_OK | X_OK) == -1) {
        dprintf(client->fd, "550 Failed to access directory.\r\n");
        return (1);
    }
    new_path = strdup(client->previous_directory);
    if (new_path == NULL) {
        dprintf(client->fd, "550 Memory allocation failed.\r\n");
        return (1);
    }
    return (update_directories(client, new_path));
}

int handle_cwd_command(poll_manager_t *manager, client_t *client, char *path)
{
    int success = 0;

    if (path == NULL) {
        dprintf(client->fd, "501 Syntax error in parameters.\r\n");
        return (1);
    }
    if (strcmp(path, "-") == 0)
        success = handle_previous_directory(client);
    else
        success = handle_directory_change(manager, client, path);
    if (success == 0)
        dprintf(client->fd, "250 Directory successfully changed.\r\n");
    return (0);
}
