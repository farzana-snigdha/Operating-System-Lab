// C program to demonstrate working of Semaphores
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;
int value = 0;

void* thread(void* arg)
{
    //wait
    sem_wait(&mutex);
    printf("\nEntered..thread\n");

    //critical section
    sleep(4);
    printf("\nValue = %d",++value);

    //signal
    printf("\nJust Exiting...\n");
    sem_post(&mutex);
}


void* thread_1(void* arg)
{
    //wait
    sem_post(&mutex);
    printf("\nEntered..thread_1\n");

    //critical section
    sleep(4);
    printf("\nValue = %d",++value);

    //signal
    printf("\nJust Exiting...\n");
    sem_wait(&mutex);
}


int main()
{
    sem_init(&mutex, 0, 0);
    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread,NULL);
    sleep(2);
    pthread_create(&t2,NULL,thread_1,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mutex);
    return 0;
}
