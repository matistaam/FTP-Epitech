/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_retr_command2
*/

#include "my.h"

void cleanup_transfer(char *buffer, FILE *file, client_t *client)
{
    free(buffer);
    fclose(file);
    close(client->data_fd);
    client->data_fd = -1;
}
