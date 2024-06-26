#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>


#define MESSAGE_SIZE 256

int main (int argc, char** argv[]) { 
    void* mmap_prt;
    int fd = open("/tmp/mmap_shared" , O_RDWR | O_CREAT ,0);
    lseek(fd ,MESSAGE_SIZE, SEEK_SET);
    write(fd, " " , 1); //fuerza que un archivo tengo un tamaño
    //puntero al espacio de memoria que estamos reservando
    mmap_prt = mmap(NULL ,MESSAGE_SIZE , PROT_READ | PROT_WRITE ,MAP_SHARED ,fd ,  0 );
    char msg[64] = "Message from mmap sender.";
    memcpy (mmap_prt , msg , MESSAGE_SIZE);
    
    return 0;
}