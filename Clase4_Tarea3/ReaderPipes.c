#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

/*
Practice
make to programas (not using fork)
communicate those two programs though named pipes
read from stdin on each program and write to the named pipe
read from the named pipe on each program and write to stdout
Tips:
    - one of them needs to read first and the other need to write first
    - you can use fgets() function to read from stdin and store into a temporary char[]
    - you can use a static size of messages of 128 chars for example
    - No puedes estar en un estado en que los dos esten bloqueados mutuamente, uno hace read y otro hace write
*/

#define FIFO_NAME "/tmp/shared_fifo"
#define MESSAGE_SIZE 128

int main()
{
    int fd;
    char message[MESSAGE_SIZE];

    mkfifo(FIFO_NAME, 0666);
    fd = open(FIFO_NAME, O_RDWR);

    if (fd == -1)
    {
        perror("Error opening pipe for reading");
        return 1;
    }

    while (1)
    {
        printf("Reader pipes: ");
        read(fd, message, sizeof(message));
        printf("%s", message);

        printf("Writer pipes: ");
        while (fgets(message, sizeof(message), stdin) == NULL)
        {
        }
        write(fd, message, strlen(message) + 1);
    }

    close(fd);
    return 0;
}