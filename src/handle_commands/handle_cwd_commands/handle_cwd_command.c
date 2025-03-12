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
    return (1);
}

int handle_path_resolution(client_t *client, char *temp_path, char **new_path,
    poll_manager_t *manager)
{
    *new_path = resolve_directory_path(temp_path);
    if (!*new_path) {
        dprintf(client->fd, "550 Failed to resolve path.\r\n");
        return (0);
    }
    if (!check_directory_access(*new_path, client->fd)) {
        free(*new_path);
        *new_path = NULL;
        return (0);
    }
    if (!is_path_allowed(manager->root_path, *new_path)) {
        dprintf(client->fd, "550 Access denied.\r\n");
        free(*new_path);
        *new_path = NULL;
        return (0);
    }
    return (1);
}

char *build_path(const char *current_dir, const char *new_path,
    poll_manager_t *manager)
{
    char *full_path = NULL;
    size_t len;

    if (!current_dir || !new_path)
        return (NULL);
    if (new_path[0] == '/' && new_path[1] == '\0')
        return (strdup(manager->root_path));
    len = strlen(current_dir) + strlen(new_path) + 2;
    full_path = malloc(len);
    if (!full_path)
        return (NULL);
    if (snprintf(full_path, len, "%s/%s", current_dir, new_path) < 0) {
        free(full_path);
        return (NULL);
    }
    return (full_path);
}

int handle_directory_change(client_t *client, char *path,
    poll_manager_t *manager)
{
    char *temp_path = NULL;
    char *new_path = NULL;

    temp_path = build_path(client->current_directory, path, manager);
    if (temp_path == NULL) {
        dprintf(client->fd, "550 Failed to change directory.\r\n");
        return (0);
    }
    if (!handle_path_resolution(client, temp_path, &new_path, manager))
        return (0);
    return (update_directories(client, new_path));
}

int handle_cwd_command(client_t *client, char *path, poll_manager_t *manager)
{
    int success = 0;

    if (path == NULL) {
        dprintf(client->fd, "501 Syntax error in parameters.\r\n");
        return (0);
    }
    if (strcmp(path, "-") == 0)
        success = handle_previous_directory(client);
    else
        success = handle_directory_change(client, path, manager);
    if (success)
        dprintf(client->fd, "250 Directory successfully changed.\r\n");
    return (0);
}
