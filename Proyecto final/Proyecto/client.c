#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc != 4) {  // Cambiado para aceptar un tercer argumento
        fprintf(stderr, "Usage: %s <server_ip> <port> <command>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char* server_ip = argv[1];
    int port = atoi(argv[2]);
    char* command = argv[3];  // Nuevo argumento del comando
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Crear el socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    // Convertir la dirección IP de texto a binario
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Conectar al servidor
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection Failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Enviar comando
    send(sock, command, strlen(command), 0);

    // Recibir respuesta
    int valread = read(sock, buffer, BUFFER_SIZE);
    if (valread < 0) {
        perror("Read error");
        close(sock);
        exit(EXIT_FAILURE);
    }
    buffer[valread] = '\0';
    printf("Response: %s\n", buffer);

    // Cerrar el socket
    close(sock);
    return 0;
}
