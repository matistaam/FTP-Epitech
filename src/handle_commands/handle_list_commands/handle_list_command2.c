/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_list_command2
*/

#include "my.h"

char *get_base_path(client_t *client, char *path, poll_manager_t *manager)
{
    if (path == NULL)
        return (strdup(client->current_directory));
    if (path[0] == '/') {
        path++;
        return (manager->root_path);
    }
    return (client->current_directory);
}
