#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

void *customer(void *num);
void *barber(void *);
sem_t waitingRoom;
sem_t barberChair;
sem_t barberSleeping;
sem_t customerWaiting;
// Flag to stop the barber thread when all customers
// have been serviced.
int allDone = 0;

int main(int argc, char *argv[])
{
    pthread_t btid;
    pthread_t tid[100];
    long RandSeed;
    int i, numCustomers, numChairs;
    int arr[100];

    printf("Enter the number of Customers : ");
    scanf("%d",&numCustomers) ;
    printf("Enter the number of Charis : ");
    scanf("%d",&numChairs);

    if (numCustomers > 100)
    {
        printf("The maximum number of Customers is %d.\n", 100);
        exit(-1);
    }

// Initialize the numbers array.
    for (i=0; i<100; i++)
    {
        arr[i] = i;
    }

// Initialize the semaphores with initial values…
    sem_init(&waitingRoom, 0, numChairs);
    sem_init(&barberChair, 0, 1);
    sem_init(&barberSleeping, 0, 0);
    sem_init(&customerWaiting, 0, 0);

// Create the barber.
    pthread_create(&btid, NULL, barber, NULL);

// Create the customers.
    for (i=0; i<numCustomers; i++)
    {
        pthread_create(&tid[i], NULL, customer, (void *)&arr[i]);
        sleep(1);
    }

// Join each of the threads to wait for them to finish.
    for (i=0; i<numCustomers; i++)
    {
        pthread_join(tid[i],NULL);
        sleep(1);
    }

// When all of the customers are finished, kill the
// barber thread.
//    allDone = 1;
    sem_post(&barberSleeping); // Wake the barber so he will exit.
    pthread_join(btid,NULL);
}

void *customer(void *number)
{
    int num = *(int *)number;

// Wait for space to open up in the waiting room…
    sem_wait(&waitingRoom);
    printf("Customer %d is waiting \n", num);

// Wait for the barber chair to become free.
    sem_wait(&barberChair);

// The chair is free so give up your spot in the
// waiting room.
    sem_post(&waitingRoom);

// Wake up the barber…
    printf("Customer %d waking the barber.\n", num);
    sem_post(&barberSleeping);

// Wait for the barber to finish cutting your hair.
    sem_wait(&customerWaiting);

// Give up the chair.
    sem_post(&barberChair);

}

void *barber(void *junk)
{
    while (!allDone)
    {
        if(!allDone)
        {
        // Sleep until someone arrives and wakes you..
            printf("The barber is sleeping\n");
            sem_wait(&barberSleeping);
            printf("The barber has finished cutting hair.\n");
        // Release the customer when done cutting…
            sem_post(&customerWaiting);
        }
        else
        {
            exit(0);
        }
    }
}


