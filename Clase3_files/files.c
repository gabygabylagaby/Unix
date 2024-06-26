#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv){

    int fd = open("files", O_RDONLY);
    
    printf("fd %d\n", fd);

    if (fd == -1)
    {
        perror("Error opening file");
        exit(1);
    }

    char buffer[20];
    int read_status = (fd, buffer, sizeof(char) * 20);

    if (read_status == -1)
    {
        perror("Error reading file");
        return 2;

    }    

    printf("File content: %s", buffer);
    close(fd);

    int fd_w = open("write-me.txt", O_CREAT | O_WRONLY, 0666);

    if (fd_w == -1)
    {
        perror("Error opening file for writing");
        exit(1);
    }

    char word[4] = {'w', 'o', 'r', 'd'};

    int write_status = write (fd_w, word, sizeof(char) * 4);

    if (write_status == -1)
    {
        perror("Error writing file");
        return 1;
    }
    
    return 0;
}
