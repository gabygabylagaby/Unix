#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

// Named Papies C (FIFO) -> estamos aqui
// Unname Pipes C 
int main(int argc, char** argv){
    int fd; 
    char* shared_fifo = "/tmp/shared_fifo";
    int fifo_status= mkfifo(shared_fifo, 0666); // crear archivo fifo con un pipe, 0666 es el permiso de lectura y escritura

    if (fifo_status == -1)
    {
        perror("Error creating fifo.");
        return 1;
    }

    fd = open(shared_fifo, O_RDWR);

    pid_t child = fork();
    if (child == -1){
        perror("Error at fork");
        return 1;
    }

    if (child == 0){
        // child process
        printf("Child process\n");
        int w_elems[10]={1,2,3,4,5,6,7,8,9,10};
        write(fd, w_elems, sizeof(int)*10);
    }else{
        // main process
        printf ("Main process\n");
        int r_elems[10];
        read (fd, r_elems, sizeof(int)*10);
        for (int i = 0; i < 10; i++)
        {
            printf("Element %d: %d\n", i, r_elems[i]);
        }
    }

    return 0;
}
