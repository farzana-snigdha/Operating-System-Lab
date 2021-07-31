#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>


void fibo(int array[],int n)
{
// initialize first and second terms
    int t1 = 0, t2 = 1;

    // initialize the next term (3rd term)
    int nextTerm = t1 + t2;

    // print 3rd to nth terms
    for (int i = 0; i <= n; ++i)
    {
        if(i==0)
        {
            array[i]=t1;
        }
        else if(i==1)
        {
            array[i]=t2;
        }
        else
        {
            array[i] = nextTerm;
            t1 = t2;
            t2 = nextTerm;
            nextTerm = t1 + t2;
        }
    }
}


void* fibonacci (void *NumOfTerms)
{

    int arr[1000];
    int n = *((int*)NumOfTerms);

    printf("\nInside the thread.\n");
    fibo(arr,n);

    // exit the current thread
    pthread_exit(arr);
}

void fun()
{
    int n;
    void *result_array;

    printf("input fibonacci terms: ");
    scanf("%d", &n);

    // Creating a new thread
    pthread_t ptid;
    pthread_create( &ptid, NULL, fibonacci, &n );

    // Waiting for the created thread to terminate
    printf("parent thread is waiting for child thread termination\n");
    pthread_join( ptid, &result_array );

    printf("parent thread > fibonacci series:\n");

    for (int j = 0; j < n; j++)
    {
        printf("%d ", ((int*)result_array)[j]);
    }
    printf("\nParent Thread ends.\n");
    pthread_exit(NULL);

}

// Driver code
int main()
{
    fun();
    return 0;
}
