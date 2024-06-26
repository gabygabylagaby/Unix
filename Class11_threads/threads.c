#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void* do_work()
{
    pthread_t t_id = pthread_self();
    printf("Thread %lu started - doing work....\n", t_id);
    sleep(1);
    printf("Thread %lu finished - ...done.\n", t_id);
    return NULL;
}


int main(int argc, char *argv[])
{
    int threads = 6;
    pthread_t thread_id[threads];

    for (int i = 0; i < threads; i++)
    {
        int t_status = pthread_create(&thread_id[i], NULL, do_work, NULL);
        if (t_status != 0)
        {
            perror("Failed to create thread");
            return 1;
        }
    }
    
    for (int i = 0; i < threads; i++)
    {
        int join_status = pthread_join(thread_id[i], NULL);
        if (join_status == -1)
        {
            perror("Failed to join thread");
            return 1;
        }
    }
    
    pthread_join(thread_id[0], NULL);

    printf("Main finished.\n");

    return 0;
}