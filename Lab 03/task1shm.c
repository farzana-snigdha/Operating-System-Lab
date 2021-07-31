#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void binarySearch(int arrSize,int inputQuery,int *str)
{
    int first = 0;
    int last = arrSize - 1;
    int middle = (first + last)/2;

    while (first <= last)
    {
        if (str[middle] < inputQuery)
            first = middle + 1;
        else if (str[middle] == inputQuery)
        {
            printf("\n%d is found\n", inputQuery);
            break;
        }
        else
            last = middle - 1;

        middle = (first + last)/2;
    }

    if (first > last)
        printf("\n%d is not found\n", inputQuery);

}
int main()
{
    // ftok to generate unique key
    //key_t key = ftok("shmfile",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(IPC_PRIVATE,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    int *str = (int*) shmat(shmid,NULL,0);

    int arr[100], arrSize, temp;

    printf("array size:\n");
    scanf("%d", &arrSize);

    printf("array values:\n");
    for(int i=0; i<arrSize; i++)
    {
        scanf("%d", &arr[i]);
    }

    for(int i=0; i<arrSize; i++)
    {
        if(arr[i]<0)
        {
            printf("\nInput: %d is a non-negative value\n", arr[i]);
            return 0;
        }
    }
    int inputQuery ;
    printf("\nEnter the value to inputQuery: \n");
    scanf("%d", &inputQuery);
    printf("\n");

    pid_t p = fork();

    if (p < 0)
    {
        printf("fork Failed" );
        return 1;
    }

    // Parent process
    else if (p > 0)
    {
        wait(NULL);
        int i;
        printf("Inside parent:");

        binarySearch(arrSize,inputQuery,str);
        //detach from shared memory
        shmdt(str);
    }

    // child process
    else
    {
        int temp;
        //sort
        for (int i = 0; i < arrSize-1; i++)
        {
            for (int j = 0; j < arrSize-j-1; j++)
            {
                if (arr[j] > arr[j+1])
                {
                    temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
        printf("child process > sorted array:\n");
        for (int j = 0; j < arrSize; j++)
        {
            printf("%d ", arr[j]);
            str[j]=arr[j];
        }

        printf("\n");

        //detach from shared memory
        shmdt(str);

        // destroy the shared memory
        shmctl(shmid,IPC_RMID,NULL);
    }
}
