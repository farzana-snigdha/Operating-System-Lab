#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

int arr[1000]={1};
int n;

sem_t semaphore;

void fibo(int n)
{

    int t1 = 0, t2 = 1;

    int nextTerm = t1 + t2;

    for (int i = 0; i <= n; ++i)
    {
        if(i==0)
        {
            arr[i]=t1;
        }
        else if(i==1)
        {
            arr[i]=t2;
        }
        else
        {
            arr[i] = nextTerm;
            t1 = t2;
            t2 = nextTerm;
            nextTerm = t1 + t2;
        }
    }
}

void* fibonacci(void* num)
{
    int n = *(int*)num;
    printf("\nInside the Child thread.\n");
    fibo(n);
    sem_post(&semaphore);
    // exit the current thread
    pthread_exit(NULL);
}

void creat_Thread()
{
    sem_init(&semaphore, 0, 0);
    printf("input Fibonacci term: ");
    scanf("%d", &n);
    pthread_t ptid;
    pthread_create(&ptid, NULL, fibonacci, (void*)&n);
    sem_wait(&semaphore);

    printf("\nFibonacci Series in Parent Thread:\n");
    for (int j = 0; j < n; j++)
    {
        printf("%d ", arr[j]);
    }
    printf("\n");
    pthread_join(ptid, NULL);
    pthread_exit(NULL);
}

int main()
{
    creat_Thread();
    return 0;
}
