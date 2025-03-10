/*
** EPITECH PROJECT, 2025
** B-NWP-400-LYN-4-1-myftp-matis.taam
** File description:
** handle_help_command
*/

#include "my.h"

int handle_help_command(client_t *client)
{
    static const char *HELP_MSG =
        "The following commands are recognized:\n"
        "USER <username> : Specify user for authentication\n"
        "PASS <password> : Specify password for authentication\n"
        "CWD <pathname>  : Change working directory\n"
        "CDUP           : Change working directory to parent directory\n"
        "QUIT           : Disconnection\n"
        "DELE <pathname> : Delete file on the server\n"
        "PWD            : Print working directory\n"
        "PASV           : Enable passive mode for data transfer\n"
        "PORT <h,p>     : Enable active mode for data transfer\n"
        "HELP           : List available commands\n"
        "NOOP           : Do nothing\n";

    dprintf(client->fd, "214 Help message.\r\n%s", HELP_MSG);
    return (0);
}
