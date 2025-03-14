/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_stor_command
*/

#include "my.h"

int write_data_to_file(client_t *client, FILE *file, char *buffer,
    ssize_t bytes_read)
{
    if (fwrite(buffer, 1, bytes_read, file) != (size_t)bytes_read) {
        cleanup_transfer(client, file, buffer);
        dprintf(client->fd, "550 Failed to write file.\r\n");
        return (1);
    }
    return (0);
}

int read_and_write_loop(client_t *client, FILE *file, char *buffer)
{
    ssize_t bytes_read = read(client->data_fd, buffer, BUFFER_SIZE);

    while (bytes_read > 0) {
        if (write_data_to_file(client, file, buffer, bytes_read) == 1)
            return (1);
        bytes_read = read(client->data_fd, buffer, BUFFER_SIZE);
    }
    if (bytes_read == -1) {
        dprintf(client->fd, "550 Failed to read data.\r\n");
        return (1);
    }
    return (0);
}

int receive_file_content(client_t *client, FILE *file)
{
    char *buffer = NULL;

    if (allocate_buffer(client, file, &buffer, BUFFER_SIZE) == 1)
        return (1);
    dprintf(client->fd, "150 Opening data connection.\r\n");
    if (read_and_write_loop(client, file, buffer) == 1) {
        cleanup_transfer(client, file, buffer);
        return (1);
    }
    cleanup_transfer(client, file, buffer);
    dprintf(client->fd, "226 Transfer complete.\r\n");
    return (0);
}

int check_and_create_file(client_t *client, FILE **file, char *path)
{
    *file = fopen(path, "wb");
    if (*file == NULL) {
        dprintf(client->fd, "550 Failed to create file.\r\n");
        return (1);
    }
    return (0);
}

int handle_stor_command(client_t *client, char *path)
{
    FILE *file = NULL;
    char *full_path = NULL;

    if (path == NULL || check_data_connection(client) == 1) {
        dprintf(client->fd, "501 Syntax error in parameters.\r\n");
        return (1);
    }
    if (build_file_path(&full_path, client->current_directory, path) == 1) {
        dprintf(client->fd, "551 Requested action aborted.\r\n");
        return (1);
    }
    if (check_and_create_file(client, &file, full_path) == 1) {
        free(full_path);
        return (1);
    }
    free(full_path);
    return (receive_file_content(client, file));
}
