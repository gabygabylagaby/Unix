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
    struct sockaddr_un server_Addr;
    server_Addr.sun_family = AF_UNIX;
    strcpy(server_Addr.sun_path, socket_path);
    int socket_size = sizeof(server_Addr);
    
    int bind_status = bind(server_socket_fd, (struct sockaddr*)&server_Addr, socket_size);
    
    if (bind_status == -1)
    {
        perror("Error at bind");
        return 1;
    }
    
    int listen_status = listen(server_socket_fd, 5);
    if (listen_status == -1)
    {
        perror("Error at listen");
        return 1;
    }
    
    struct sockaddr_un client_addr;
    int socket_size_client = sizeof(client_addr);
    int client_sockets_fd = accept(server_socket_fd, (struct sockaddr*)&client_addr, &socket_size_client);

    if (client_sockets_fd == -1)
    {
        perror("Error at accept");
        return 1;
    }

    char buffer[64];
    read(client_sockets_fd, &buffer, 64);
    printf("Read from client: %s\n", buffer);
    write(client_sockets_fd, "Hello from server", 18);
    close(client_sockets_fd);
    close(server_socket_fd);
    return 0;
}