/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_quit_command
*/

#include "my.h"

int handle_quit_command(client_t *client)
{
    dprintf(client->fd, "221 Service closing control connection.\r\n");
    return (-1);
}
