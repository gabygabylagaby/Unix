#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main (int argc, char** argv[]) { 
    int shm_id;
    void* shm_prt;
    char buffer[256];
    shm_id = shmget((key_t)3475,SHM_SIZE , 0666);
    if(shm_id == -1)
    {
        perror("Error at get shared memory.");
        return 1 ;
    }
    //nos devuelve un puntero a esa seccion de memoria
    shm_prt = shmat(shm_id , NULL , 0);  
    printf("Message read from shared memory : %s\n" ,(char*) shm_prt);
    return 0; 
}