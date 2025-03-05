/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_user_command
*/

#include "my.h"

int handle_user_command(client_t *client, char *command)
{
    if (command == NULL) {
        dprintf(client->fd, "501 Syntax error in parameters.\r\n");
        return (0);
    }
    client->username = strdup(command);
    dprintf(client->fd, "331 User name okay, need password.\r\n");
    return (0);
}
