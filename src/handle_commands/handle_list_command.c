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

void list_directory_content(DIR *dir, int data_fd, const char *base_path)
{
    struct dirent *entry = NULL;
    struct stat st = {0};
    char *fullpath = NULL;
    size_t path_len = 0;

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

int open_directory(client_t *client, DIR **dir, char *target_path)
{
    *dir = opendir(target_path);
    if (*dir == NULL) {
        dprintf(client->fd, "550 Failed to open directory.\r\n");
        free(target_path);
        return (1);
    }
    dprintf(client->fd,
    "150 File status okay; about to open data connection.\r\n");
    return (0);
}

int check_data_connection(client_t *client)
{
    if (client->data_fd == -1) {
        dprintf(client->fd, "425 Use PORT or PASV first.\r\n");
        return (1);
    }
    return (0);
}

int handle_list_command(poll_manager_t *manager, client_t *client, char *path)
{
    DIR *dir = NULL;
    char *target_path = NULL;

    if (check_data_connection(client) == 1)
        return (1);
    target_path = get_path(manager, client, path);
    if (target_path == NULL) {
        dprintf(client->fd, "550 Failed to access path.\r\n");
        return (1);
    }
    if (open_directory(client, &dir, target_path) == 1)
        return (1);
    list_directory_content(dir, client->data_fd, target_path);
    cleanup_and_close(client, dir, target_path, path);
    return (0);
}
