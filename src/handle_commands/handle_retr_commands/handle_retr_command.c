/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_retr_command
*/

#include "my.h"

int allocate_buffer(client_t *client, char **buffer, size_t size,
    FILE *file)
{
    *buffer = malloc(size);
    if (!*buffer) {
        fclose(file);
        return (dprintf(client->fd, "551 Requested action aborted.\r\n"), 0);
    }
    return (1);
}

int send_file_content(client_t *client, FILE *file, size_t file_size)
{
    char *buffer;
    size_t bytes;

    if (!allocate_buffer(client, &buffer, file_size, file))
        return (0);
    dprintf(client->fd, "150 Opening data connection.\r\n");
    bytes = fread(buffer, 1, file_size, file);
    if (bytes > 0)
        write(client->data_fd, buffer, bytes);
    cleanup_transfer(buffer, file, client);
    dprintf(client->fd, "226 Transfer complete.\r\n");
    return (1);
}

int check_and_open_file(client_t *client, char *path, FILE **file,
    struct stat *st)
{
    if (!path || !check_data_connection(client))
        return (dprintf(client->fd, "501 Syntax error in parameters.\r\n"), 0);
    *file = fopen(path, "rb");
    if (stat(path, st) == -1 || *file == NULL)
        return (dprintf(client->fd, "550 Failed to open file.\r\n"), 0);
    return (1);
}

char *build_full_path(client_t *client, const char *path)
{
    char *full_path = malloc(strlen(client->current_directory) + strlen(path)
    + 2);

    if (!full_path)
        return (NULL);
    sprintf(full_path, "%s/%s", client->current_directory, path);
    return (full_path);
}

int handle_retr_command(client_t *client, char *path)
{
    FILE *file = NULL;
    struct stat st = {0};
    char *full_path = NULL;

    if (!path || !check_data_connection(client))
        return (dprintf(client->fd, "501 Syntax error in parameters.\r\n"), 0);
    full_path = build_full_path(client, path);
    if (full_path == NULL)
        return (dprintf(client->fd, "551 Requested action aborted.\r\n"), 0);
    if (!check_and_open_file(client, full_path, &file, &st)) {
        free(full_path);
        return (0);
    }
    free(full_path);
    return (send_file_content(client, file, st.st_size));
}
