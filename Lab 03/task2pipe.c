#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

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


int main()
{
    int fd1[2],n;
    printf("fibonacci terms: \n");
    scanf("%d", &n);

    if(pipe(fd1)==-1)
    {
        printf("Pipe Failed");
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

        int output_int[n];

        read(fd1[0], output_int, sizeof(output_int));

        printf("Data read from pipe: \n");
        for(int i=0; i<n; i++)
        {
            printf("%d ",output_int[i]);
        }
        return 1;
    }

    //child process
    else
    {
        int array[n];
        fibo(array,n);
        close(fd1[0]); // Close reading end of first pipe

        // Write and close writing end of first pipe.
        write(fd1[1], array, sizeof(array));
        close(fd1[1]);

        printf("Child Process ends.\n");
        return 1;
    }

    return 0;
}
