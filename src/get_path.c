/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** get_path
*/

#include "my.h"

int is_path_allowed(const char *root, const char *path)
{
    char *root_realpath = realpath(root, NULL);
    char *path_realpath = realpath(path, NULL);
    int allowed = 0;

    if (root_realpath == NULL || path_realpath == NULL) {
        if (root_realpath != NULL)
            free(root_realpath);
        if (path_realpath != NULL)
            free(path_realpath);
        return (1);
    }
    allowed = strncmp(path_realpath, root_realpath,
    strlen(root_realpath)) == 0;
    free(root_realpath);
    free(path_realpath);
    return (!allowed);
}

char *resolve_and_check_path(char *full_path, const char *root_path)
{
    char *resolved_path = NULL;

    resolved_path = realpath(full_path, NULL);
    free(full_path);
    if (resolved_path == NULL || is_path_allowed(root_path, resolved_path)
    == 1) {
        free(resolved_path);
        return (NULL);
    }
    return (resolved_path);
}

char *build_relative_path(const char *current_dir, const char *path)
{
    char *full_path = NULL;
    size_t len = 0;

    len = strlen(current_dir) + strlen(path) + 2;
    full_path = malloc(len);
    if (full_path == NULL)
        return (NULL);
    sprintf(full_path, "%s/%s", current_dir, path);
    return (full_path);
}

char *build_absolute_path(const char *root_path, const char *path)
{
    char *full_path = NULL;
    size_t len = 0;

    path++;
    len = strlen(root_path) + strlen(path) + 2;
    full_path = malloc(len);
    if (full_path == NULL)
        return (NULL);
    sprintf(full_path, "%s/%s", root_path, path);
    return (full_path);
}

char *get_path(poll_manager_t *manager, client_t *client, const char *path)
{
    char *full_path = NULL;

    if (path == NULL)
        return (strdup(client->current_directory));
    if (path[0] == '/')
        full_path = build_absolute_path(manager->root_path, path);
    else
        full_path = build_relative_path(client->current_directory, path);
    if (full_path == NULL)
        return (NULL);
    return (resolve_and_check_path(full_path, manager->root_path));
}
