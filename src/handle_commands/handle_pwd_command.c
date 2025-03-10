/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_pwd_command
*/

#include "my.h"

int handle_pwd_command(client_t *client)
{
    dprintf(client->fd, "257 \"%s\" is current directory.\r\n",
    client->current_directory ? client->current_directory : "/");
    return (0);
}
