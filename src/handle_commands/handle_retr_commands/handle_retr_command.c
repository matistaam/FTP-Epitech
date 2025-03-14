/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_retr_command
*/

#include "my.h"

int allocate_buffer(client_t *client, FILE *file, char **buffer, size_t size)
{
    *buffer = malloc(size);
    if (*buffer == NULL) {
        fclose(file);
        dprintf(client->fd, "551 Requested action aborted.\r\n");
        return (1);
    }
    return (0);
}

int send_file_content(client_t *client, FILE *file, size_t file_size)
{
    char *buffer = NULL;
    size_t bytes = 0;

    if (allocate_buffer(client, file, &buffer, file_size) == 1)
        return (1);
    dprintf(client->fd, "150 Opening data connection.\r\n");
    bytes = fread(buffer, 1, file_size, file);
    if (bytes > 0)
        write(client->data_fd, buffer, bytes);
    cleanup_transfer(client, file, buffer);
    dprintf(client->fd, "226 Transfer complete.\r\n");
    return (0);
}

int check_and_open_file(client_t *client, struct stat *st, FILE **file,
    char *path)
{
    if (path == NULL || check_data_connection(client) == 1) {
        dprintf(client->fd, "501 Syntax error in parameters.\r\n");
        return (1);
    }
    *file = fopen(path, "rb");
    if (stat(path, st) == -1 || *file == NULL) {
        dprintf(client->fd, "550 Failed to open file.\r\n");
        return (1);
    }
    return (0);
}

int handle_retr_command(poll_manager_t *manager, client_t *client, char *path)
{
    FILE *file = NULL;
    struct stat st = {0};
    char *full_path = NULL;

    if (path == NULL || check_data_connection(client) == 1) {
        dprintf(client->fd, "501 Syntax error in parameters.\r\n");
        return (1);
    }
    full_path = get_path(manager, client, path);
    if (full_path == NULL) {
        dprintf(client->fd, "551 Requested action aborted.\r\n");
        return (1);
    }
    if (check_and_open_file(client, &st, &file, full_path) == 1) {
        free(full_path);
        return (1);
    }
    free(full_path);
    return (send_file_content(client, file, st.st_size));
}
