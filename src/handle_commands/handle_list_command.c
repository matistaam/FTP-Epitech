/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_list_command
*/

#include "my.h"

void cleanup_and_close(client_t *client, DIR *dir, char *target_path,
    char *path)
{
    if (path != NULL && target_path != client->current_directory)
        free(target_path);
    closedir(dir);
    dprintf(client->fd, "226 Directory send OK.\r\n");
    close(client->data_fd);
    client->data_fd = -1;
}

void list_directory_content(int data_fd, DIR *dir, const char *base_path)
{
    struct dirent *entry;
    struct stat st;
    char *fullpath;
    size_t path_len;

    entry = readdir(dir);
    while (entry != NULL) {
        path_len = strlen(base_path) + strlen(entry->d_name) + 2;
        fullpath = malloc(path_len);
        if (fullpath == NULL)
            continue;
        snprintf(fullpath, path_len, "%s/%s", base_path, entry->d_name);
        if (stat(fullpath, &st) == 0)
            dprintf(data_fd, "%s\r\n", entry->d_name);
        free(fullpath);
        entry = readdir(dir);
    }
}

int check_data_connection(client_t *client)
{
    if (client->data_fd == -1) {
        dprintf(client->fd, "425 Use PORT or PASV first.\r\n");
        return (0);
    }
    return (1);
}

char *get_target_path(client_t *client, char *path)
{
    char *target_path;

    if (path != NULL) {
        if (path[0] == '/') {
            return (path);
        }
        target_path = malloc(strlen(client->current_directory) + strlen(path)
        + 2);
        if (target_path == NULL)
            return (client->current_directory);
        sprintf(target_path, "%s/%s", client->current_directory, path);
        return (target_path);
    }
    return (client->current_directory);
}

int handle_list_command(client_t *client, char *path)
{
    DIR *dir;
    char *target_path = get_target_path(client, path);

    if (!check_data_connection(client))
        return (0);
    dir = opendir(target_path);
    if (dir == NULL) {
        dprintf(client->fd, "550 Failed to open directory.\r\n");
        if (path != NULL && target_path != client->current_directory)
            free(target_path);
        return (0);
    }
    dprintf(client->fd,
    "150 File status okay; about to open data connection.\r\n");
    list_directory_content(client->data_fd, dir, target_path);
    cleanup_and_close(client, dir, target_path, path);
    return (0);
}
