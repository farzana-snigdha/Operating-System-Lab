#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

void binarySearch(int arrSize,int inputQuery, int output_int[])
{
    int first = 0;
    int last = arrSize - 1;
    int middle = (first + last)/2;

    while (first <= last)
    {
        if (output_int[middle] < inputQuery)
            first = middle + 1;
        else if (output_int[middle] == inputQuery)
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
    int fd1[2],arr[100], arrSize;

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

    int inputQuery;
    printf("input query: \n");
    scanf("%d", &inputQuery);
    printf("\n");

    if(pipe(fd1)==-1)
    {
        printf("pipe Failed");
    }
    pid_t p;
    p = fork();

    if(p<0)
    {
        printf("fork failed");
    }

    //Parent Process
    else if(p > 0)
    {
        wait(NULL);
        close(fd1[1]);

        int output_int[arrSize];

        read(fd1[0], output_int, sizeof(output_int));

        printf("\nData read from pipe: \n");
        for( int i=0; i<sizeof(output_int); i++)
        {
            if(i<arrSize)
            {
                printf("%d ",output_int[i]);
            }
        }

        // Binary Search
        binarySearch(arrSize,inputQuery,output_int);
        return 1;
    }

    //child process

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
        }

        close(fd1[0]); // Close reading end of first pipe

        // Write and close writing end of first pipe.
        write(fd1[1], arr, sizeof(arr));
        close(fd1[1]);

        return 1;
    }

    return 0;
}
