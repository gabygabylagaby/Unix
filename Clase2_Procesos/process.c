#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){
    
    printf("Main pid: %d, parend pid: %d\n", getpid(), getppid());

    //sleep(10);

    pid_t child_pid_status = fork();

    if (child_pid_status == 0){
        // child process
        printf("at Child process pid(%d), ppid(%d)\n", getpid(), getppid());
        sleep(5);
        printf("Finish child block.\n", getpid(), getppid());
    }else{
        // parent process
        printf("main process pid(%d), ppid(%d)\n", getpid(), getppid());
        wait(NULL);
        printf("Finish parent block.\n", getpid(), getppid());
    }
    
    /**
     * Necesito tres niveles de ejecucion deferentes, el padre espera al nieto y el nieto espera al hijo. simula un sleep de 5 segundos y otro de 10 segundos
     * El padre no puede morir hasta que el hijo haya terminado y sus nietos.
    */
    printf("Finish main process pid(%d), ppid(%d).\n ", getpid(), getppid());

    return 0;
}
