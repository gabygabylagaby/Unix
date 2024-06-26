#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MESSAGE_SIZE 64

struct msg_struct
{
    long msg_type;
    char msg_content[MESSAGE_SIZE];
};

int main(int argc, char *argv[])
{
    int msg_queue_id;
    struct msg_struct message;
    char buffer[MESSAGE_SIZE];
    int exit = 0;

    msg_queue_id = msgget((key_t)5678, IPC_CREAT | 0666);
    if (msg_queue_id == -1)
    {
        perror("Error at message queue get");
        return 1;
    }
    message.msg_type = 1;
    // message.msg_content[0] = 'A';

    while (!exit)
    {
        printf("Enter a message to send:\n");
        fgets(buffer, MESSAGE_SIZE, stdin);

        strcpy(message.msg_content, buffer);

        msgsnd(msg_queue_id, (void *)&message, MESSAGE_SIZE, 0);
        printf("Message sent to queue: %s\n", message.msg_content);

        if (strncmp(buffer, "exit", 4) == 0)
        {
            exit = 1;
        }
    }

    printf("Sender finish\n");

    return 0;
}