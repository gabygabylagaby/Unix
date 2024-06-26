#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>

void sigCount_handler(int signum)
{
    printf("sigCount_handler killed\n");
}

void sigTop_handler(int signum)
{
    printf("sigTop_handler killed\n");
}

void signint_handler(int signum)
{
    printf("Ctrl+c detected, exiting the program\n");
    exit(0);
}

int main (int argc, char** argv[]) { 
    int child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error at fork");
        return 1;
    }

    signal(SIGINT, &signint_handler);

    if (child_pid == 0)
    {
        signal(SIGSTOP, &sigTop_handler);
        signal(SIGCONT, &sigCount_handler);
        int counter = 0;
        while (1)
        {
            printf("child counter %d\n", counter++);
            sleep(1);
        }
        
    } else {
        sleep(6);
        kill(child_pid, SIGSTOP);
        sleep(6);
        kill(child_pid, SIGCONT);   
        sleep(6);
        kill(child_pid, SIGKILL);
        wait(NULL);
    }
    
    return 0;
}