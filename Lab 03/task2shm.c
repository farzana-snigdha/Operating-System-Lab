#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void fibo(int *str,int n)
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
            str[i]=t1;
        }
        else if(i==1)
        {
            str[i]=t2;
        }
        else
        {
            str[i] = nextTerm;
            t1 = t2;
            t2 = nextTerm;
            nextTerm = t1 + t2;
        }
    }
}

int main()
{
    // ftok to generate unique key
    //key_t key = ftok("shmfile",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(IPC_PRIVATE,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    int *str = (int*) shmat(shmid,NULL,0);

    int n;

    printf("Enter the number of terms: \n");
    scanf("%d", &n);

    pid_t p;
    p = fork();

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
        for(i=0; i<n; i++)
        {
            printf("%d ",str[i]);
        }
        printf("\n");

        //detach from shared memory
        shmdt(str);
    }

    // child process
    else
    {
        int i, array[n];
        fibo(str,n);
        //detach from shared memory
        shmdt(str);

        // destroy the shared memory
        shmctl(shmid,IPC_RMID,NULL);

    }
}
