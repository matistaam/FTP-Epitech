/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** parse_ftp_command
*/

#include "my.h"

int check_authentication(client_t *client, const char *command)
{
    if (client->is_authenticated || strcasecmp(command, "USER") == 0 ||
        strcasecmp(command, "PASS") == 0 || strcasecmp(command, "QUIT") == 0)
        return (1);
    dprintf(client->fd, "530 Please login with USER and PASS.\r\n");
    return (0);
}

int execute_command(client_t *client, const char *command, char *args)
{
    if (strcasecmp(command, "USER") == 0)
        return (handle_user_command(client, args));
    if (strcasecmp(command, "PASS") == 0)
        return (handle_pass_command(client, args));
    if (strcasecmp(command, "QUIT") == 0)
        return (handle_quit_command(client));
    if (strcasecmp(command, "NOOP") == 0)
        return (handle_noop_command(client));
    if (strcasecmp(command, "PWD") == 0)
        return (handle_pwd_command(client));
    if (strcasecmp(command, "CWD") == 0)
        return (handle_cwd_command(client, args));
    if (strcasecmp(command, "CDUP") == 0)
        return (handle_cwd_command(client, ".."));
    dprintf(client->fd, "500 Unknown command.\r\n");
    return (0);
}

int parse_ftp_command(client_t *client, char *buffer)
{
    char *args = NULL;
    char *command = strdup(buffer);
    int ret = 0;

    if (command == NULL)
        return (-1);
    command[strcspn(command, "\r\n")] = 0;
    args = strchr(command, ' ');
    if (args != NULL) {
        *args = '\0';
        args++;
    }
    if (check_authentication(client, command))
        ret = execute_command(client, command, args);
    free(command);
    return (ret);
}
