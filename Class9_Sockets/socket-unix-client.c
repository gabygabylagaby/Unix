#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char* socket_path = "/tmp/sock_server";
    int server_socket_fd;
    server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_fd == -1)
    {
        perror("Error at socket creation");
        return 1;
    }

    struct sockaddr_un server_sockets_Addr;
    server_sockets_Addr.sun_family = AF_UNIX;
    strcpy(server_sockets_Addr.sun_path, socket_path);

    int connect_status = connect(server_socket_fd, (struct sockaddr*)&server_sockets_Addr, sizeof(server_sockets_Addr));
    
    if (connect_status == -1)
    {
        perror("Error at connect");
        return 1;
    }

    char buffer[64];
    write(server_socket_fd, "Hello from client", 18);
    read(server_socket_fd, &buffer, 64);
    printf("Read from server: %s\n", buffer);
    close(server_socket_fd);
    close(server_socket_fd);
    return 0;
}