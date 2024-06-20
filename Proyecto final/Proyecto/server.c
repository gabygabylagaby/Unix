#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>

#define MAX_CONN 30
#define BUFFER_SIZE 1024
#define SERVICE_NAME "Gaby’s service"
#define SERVICE_VERSION "v0.1"

void handle_client(int client_socket);
void signal_handler(int sig);

int server_socket;

void* client_thread(void* arg) {
    int client_socket = *((int*)arg);
    free(arg);
    handle_client(client_socket);
    close(client_socket);
    return NULL;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) {
        return;
    }
    buffer[bytes_read] = '\0';

    char response[BUFFER_SIZE];
    if (strcmp(buffer, "getInfo") == 0) {
        snprintf(response, sizeof(response), "%s, %s", SERVICE_NAME, SERVICE_VERSION);
    } else if (strcmp(buffer, "getNumberOfPartitions") == 0) {
        FILE* fp = popen("lsblk -l | grep part | wc -l", "r");
        if (fp == NULL) {
            snprintf(response, sizeof(response), "Error executing command");
        } else {
            fgets(response, sizeof(response), fp);
            pclose(fp);
        }
    } else if (strcmp(buffer, "getCurrentKernelVersion") == 0) {
        FILE* fp = popen("uname -r", "r");
        if (fp == NULL) {
            snprintf(response, sizeof(response), "Error executing command");
        } else {
            fgets(response, sizeof(response), fp);
            pclose(fp);
        }
    } else if (strcmp(buffer, "sshdRunning") == 0) {
        if (access("/var/run/sshd.pid", F_OK) != -1) {
            snprintf(response, sizeof(response), "true");
        } else {
            snprintf(response, sizeof(response), "false");
        }
    } else {
        snprintf(response, sizeof(response), "Unknown command");
    }

    write(client_socket, response, strlen(response));
}

void signal_handler(int sig) {
    printf("\nServer is shutting down...\n");
    close(server_socket);
    exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_CONN) == -1) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, signal_handler);
    printf("Server listening on port %d\n", port);

    while (1) {
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }

        pthread_t tid;
        int* pclient = malloc(sizeof(int));
        if (pclient == NULL) {
            perror("Failed to allocate memory");
            close(client_socket);
            continue;
        }
        *pclient = client_socket;
        if (pthread_create(&tid, NULL, client_thread, pclient) != 0) {
            perror("Thread creation failed");
            close(client_socket);
            free(pclient);
        }
    }

    close(server_socket);
    return 0;
}
