#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>


#define MESSAGE_SIZE 256

int main (int argc, char** argv[]) { 
    void* mmap_prt;
    int fd = open("/tmp/mmap_shared" , O_RDWR ,0666);
    mmap_prt = mmap(NULL ,MESSAGE_SIZE , PROT_WRITE | PROT_READ ,MAP_SHARED ,fd ,  0 );
    if(mmap_prt == -1)
    {
        perror("Error getting map");
        return 1 ;
    }


    char msg[64];
    memcpy ( msg , mmap_prt,MESSAGE_SIZE);
    printf ("Message read from mmap: %s\n" , msg);
    return 0;
}