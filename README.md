# MyFTP Server

A simple FTP server implementation following the RFC 959 protocol specification. This server supports basic FTP commands and provides file transfer capabilities.

## 🚀 Features

- Anonymous user authentication
- File operations (upload, download, delete)
- Directory navigation
- Active and passive transfer modes
- Basic FTP commands support

## 📋 Supported Commands

| Command | Description |
|---------|-------------|
| USER    | Specify username for authentication |
| PASS    | Specify password for authentication |
| CWD     | Change working directory |
| CDUP    | Change to parent directory |
| QUIT    | Disconnect from server |
| DELE    | Delete file on server |
| PWD     | Print working directory |
| PASV    | Enable passive mode |
| PORT    | Enable active mode |
| HELP    | List available commands |
| NOOP    | No operation |
| RETR    | Download file |
| STOR    | Upload file |
| LIST    | List directory contents |

## 🛠️ Building the Project

```sh
# Clone the repository
git clone <repository-url>

# Build the server
make

# Clean build files
make clean

# Full clean (including executable)
make fclean

# Rebuild
make re
```

## 🚦 Usage

```sh
./myftp port path

# Arguments:
#   port: Port number on which the server socket listens
#   path: Path to the home directory for the Anonymous user
```

## 📝 Example

```sh
# Start server on port 2121 with /home/ftp as root directory
./myftp 2121 /home/ftp
```

## 🔒 Authentication

The server supports anonymous access:
- Username: Anonymous
- Password: (empty)

## 📄 Protocol Specification

This FTP server implementation follows the RFC 959 protocol specification. For detailed information about supported commands and their responses, please refer to the [EPITECH-MyFTP-Protocol-(RFC959-Extract).txt](EPITECH-MyFTP-Protocol-(RFC959-Extract).txt) file.

## ⚠️ Note

This is an educational project. Do not use in production environments.
