/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_noop_command
*/

#include "my.h"

int handle_noop_command(client_t *client)
{
    dprintf(client->fd, "200 Command okay.\r\n");
    return (0);
}
