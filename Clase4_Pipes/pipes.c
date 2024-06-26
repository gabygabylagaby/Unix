#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Named Papies C (FIFO)
// Unname Pipes C -> estamos aqui
int main(int argc, char** argv){
    pid_t child;
    int fd[2];
    pipe(fd);

    int pipe_status = pipe(fd);

    // El fork crea un proceso hijo que es una copia exacta del padre
    if (pipe_status == -1)
    {
        perror("Error creating pipe");
        return 1;
    }
    
    child = fork();

    if (child == -1)
    {
        perror("Error creating child process");
        return 1;
    }

    if (child == 0)
    {
        // child process
        printf ("Child process\n");
        close(fd[0]);
        char message [50] = "Hi from child.";
        printf("Sending message '%s' from pid(%d) with ppid (%d)\n", message, getpid(), getppid());
        fd[1] = write(fd[1], message, strlen(message));
        printf("Finish child process\n");
    }else{
        // main process
        printf ("Main process\n");
        close(fd[1]);

        char message_read[50];
        printf("Sending message '%s' from pid(%d) with ppid (%d)\n", message_read, getpid(), getppid());

        fd[0] = read(fd[0], message_read, sizeof(message_read));

        printf("Finish main process\n");
    }
    

    return 0;
}
