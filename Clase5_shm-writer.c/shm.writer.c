#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main (int argc, char** argv[]) { 
    int shm_id;
    void* shm_prt;
    char buffer[256];
    //recibe 3 argummento el key , tamaño de memoria que queremos solucionar , y las bandera relacionadas a los permisos
    //debe obtener un segmento de memoria , crea un segmento de memoria
    shm_id = shmget((key_t)3475,SHM_SIZE , 0666 | IPC_CREAT);
    if(shm_id == -1)
    {
        perror("Error at segment.");
        return 1 ;
    }
    //si se pasa null el SO se encarga de administra la referencia o direccion
    //solo para este ejemplo , pero cuando necesitamos tener el control de ese sector de memori si es necesario colocar algo distinto de null
    //attach a ese espacio de memoria
    shm_prt = shmat(shm_id , NULL , 0);  
    printf("Enter message for shared memory \n");
    //leemos
    read(0 , buffer , 256);
    //deberiamos haber copiado en el sector de memoria compartido lo que acabamos de leer
    strcpy(shm_prt , buffer); 
    printf("Message sent: %s\n , buffer");

    return 0;
}