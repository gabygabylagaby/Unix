#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

#define MESSAGE_SIZE 64

struct msg_struct{
    long msg_type;
    char msg_content[MESSAGE_SIZE];
};

int main (int argc, char** argv) { 
    int msg_queue_id;
    struct msg_struct message;
    int exit = 0;

    msg_queue_id =msgget((key_t)5678 , 0666);
    if(msg_queue_id == -1)
    {
        perror("Error getting queue");
        return 1;
    }

    msgrcv(msg_queue_id, (void*)&message, MESSAGE_SIZE, 0, 0);
    printf("Message read from queue: %s\n", message.msg_content);

    msgctl(msg_queue_id, IPC_RMID, 0);

    while (!exit)
    {
        msgrcv(msg_queue_id, (void*)&message, MESSAGE_SIZE, 0, 0);
        printf("Message read from queue: %s\n", message.msg_content);

        if (strncmp(message.msg_content, "exit", 4) == 0)
        {
            exit = 1;
        }
        
    }

    msgctl(msg_queue_id, IPC_RMID, 0);

    /*
    P1 <-> P2
    Comunicacion entre procesos:
    1. Shared Memory
    2. Pipe
    3. Message Queue
    4. Named Pipe

    Counting Semaphore: Semaforo binario

    External process open Signals
    
    Process open - process call : fork - exec
    popen POSIX : pipe open implement

    */

    return 0;
}