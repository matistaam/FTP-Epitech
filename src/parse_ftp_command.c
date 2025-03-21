/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** parse_ftp_command
*/

#include "my.h"

int execute_command2(poll_manager_t *manager, client_t *client,
    const char *command, char *args)
{
    if (strcasecmp(command, "STOR") == 0)
        return (handle_stor_command(client, args));
    if (strcasecmp(command, "RETR") == 0)
        return (handle_retr_command(manager, client, args));
    if (strcasecmp(command, "LIST") == 0)
        return (handle_list_command(manager, client, args));
    if (strcasecmp(command, "DELE") == 0)
        return (handle_dele_command(manager, client, args));
    if (strcasecmp(command, "PWD") == 0)
        return (handle_pwd_command(manager, client));
    if (strcasecmp(command, "HELP") == 0)
        return (handle_help_command(client));
    if (strcasecmp(command, "NOOP") == 0)
        return (handle_noop_command(client));
    return (-1);
}

int execute_command(poll_manager_t *manager, client_t *client,
    const char *command, char *args)
{
    int ret = 0;

    if (strcasecmp(command, "USER") == 0)
        return (handle_user_command(client, args));
    if (strcasecmp(command, "PASS") == 0)
        return (handle_pass_command(client, args));
    if (strcasecmp(command, "CWD") == 0)
        return (handle_cwd_command(manager, client, args));
    if (strcasecmp(command, "CDUP") == 0)
        return (handle_cdup_command(manager, client));
    if (strcasecmp(command, "QUIT") == 0)
        return (handle_quit_command(client));
    if (strcasecmp(command, "PORT") == 0)
        return (handle_port_command(client, args));
    if (strcasecmp(command, "PASV") == 0)
        return (handle_pasv_command(client));
    ret = execute_command2(manager, client, command, args);
    if (ret == -1)
        dprintf(client->fd, "500 Unknown command.\r\n");
    return (0);
}

int check_authentication(client_t *client, const char *command)
{
    if (client->is_authenticated || strcasecmp(command, "USER") == 0 ||
        strcasecmp(command, "PASS") == 0 || strcasecmp(command, "QUIT") == 0)
        return (1);
    dprintf(client->fd, "530 Please login with USER and PASS.\r\n");
    return (0);
}

int parse_ftp_command(poll_manager_t *manager, client_t *client, char *buffer)
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
    if (check_authentication(client, command) == 1)
        ret = execute_command(manager, client, command, args);
    free(command);
    return (ret);
}
