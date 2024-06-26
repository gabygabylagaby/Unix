#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>


#define MESSAGE_SIZE 256

int main (int argc, char** argv[]) { 
    FILE* process_pipe;
    char* chars[6] = {"and", "true", "error", "boy", "false", "die"};

    char* process = "/usr/bin/sort";
    process_pipe = popen(process, "w");

    for (int i = 0; i < 6; i++)
    {
        fputs(chars[i], process_pipe);
        fputs("\n", process_pipe);

    }
    pclose(process_pipe);
    
    return 0;
}