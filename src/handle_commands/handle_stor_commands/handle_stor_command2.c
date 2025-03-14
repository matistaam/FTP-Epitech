/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_stor_command2
*/

#include "my.h"

int build_file_path(char **full_path, const char *current_dir,
    const char *filename)
{
    size_t len = strlen(current_dir) + strlen(filename) + 2;

    *full_path = malloc(len);
    if (*full_path == NULL)
        return (1);
    sprintf(*full_path, "%s/%s", current_dir, filename);
    return (0);
}
