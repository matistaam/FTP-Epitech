/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_pass_command
*/

#include "my.h"

int handle_pass_command(client_t *client, char *command)
{
    if (client->username == NULL) {
        dprintf(client->fd, "503 Login with USER first.\r\n");
        return (0);
    }
    if (strcmp(client->username, "Anonymous") == 0 &&
    (command == NULL || strlen(command) == 0)) {
        client->is_authenticated = true;
        dprintf(client->fd, "230 User logged in, proceed.\r\n");
    } else {
        dprintf(client->fd, "530 Login incorrect.\r\n");
    }
    return (0);
}
