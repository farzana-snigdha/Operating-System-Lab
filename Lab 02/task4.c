#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{

    for (int i = 0; i < n-1; i++)

        for (int j = 0; j < n-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                swap(&arr[j], &arr[j+1]);
            }

        }
}


void printArray(int arr[], int size)
{

    for (int i=0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}


int main()
{
    pid_t pid1;
    int x = 0, array[1000], size;

    printf("array: ");
    scanf("%d", &size);

    for(int i=0; i<size; i++)
    {
        scanf("%d", &array[i]);
    }


    printf("\n value: ");
    scanf("%d", &x);

    while(x <= 0)
    {
        printf("provided number must be larger than 0 ");
        scanf("%d", &x);
    }

    pid1 = fork();


    if(pid1 < 0)
    {
        printf("failed\n");
    }
    else if (pid>0)
    {
        wait(NULL);
        int i;
        for(i=0; i<size; i++)
        {
            if(array[i] == x)
            {
                printf("position %d\n", i);
                break;
            }
        }

        if(i == size)
        {
            printf("provide value is not in the array \n");
        }


    }
    else if(pid1 == 0)
    {
        bubbleSort(array, size);
        printf("\n sorted array:  ");
        printArray(array, size);
    }


    return 0;
}


