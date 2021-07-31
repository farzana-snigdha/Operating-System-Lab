#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
    int fd1[2];  // Used to store two ends of first pipe
    int fd2[2];  // Used to store two ends of second pipe


    pid_t p;

    if (pipe(fd1)==-1)
    {
        printf("Pipe Failed" );
        return 1;
    }
    if (pipe(fd2)==-1)
    {
        printf("Pipe Failed" );
        return 1;
    }

    p = fork();

    if (p < 0)
    {
        printf("fork Failed" );
        return 1;
    }

    // Parent process
    else if (p > 0)
    {
        int i,output_int[10], fixed_int[10] = {0,1,2,3,4,5,6,7,8,9};

        close(fd1[0]);  // Close reading end of first pipe

        // Write and close writing end of first pipe.
        write(fd1[1], fixed_int, 10*sizeof(int));

        printf("Data written in pipe: \n");

        close(fd1[1]);

        // Wait for child to send a string
        wait(NULL);

        read(fd2[0], output_int, 100);

        printf("Data read from pipe: \n");
        for(i=0;i<10;i++)
        {
            printf("%d ",output_int[i]);
        }
        printf("\n");

        close(fd2[0]);


    }

    // child process
    else
    {
        close(fd1[1]);  // Close writing end of first pipe

        // Read using first pipe
        int outp_int[10],i;
        read(fd1[0], outp_int, 100);

        printf("Data read from pipe: \n");
        for(i=0;i<10;i++)
        {
            printf("%d ",outp_int[i]);
            if(outp_int[i]%2==1)
                outp_int[i]+=5;
            else if(outp_int[i]%2==0)
                outp_int[i]+=10;

        }
        printf("\n");

        close(fd1[0]);

        close(fd2[0]);

        write(fd2[1], outp_int, 10*sizeof(int));

        close(fd2[1]);


        exit(0);
    }
}
