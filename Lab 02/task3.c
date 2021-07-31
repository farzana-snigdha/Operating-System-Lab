
#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>

void fib(int n)
{
    int n1 = 0, n2 = 1;
    printf("%d   ", n1);
    int sum;

    for (int i = 1; i < n; i++)
    {
        printf("%d   ", n2);
        sum = n1 + n2;
        n1 = n2;
        n2 = sum;

    }
    printf("\n");
}

int main()
{
    int x = 0;
    pid_t pid1;

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
    }
    else if(pid1 == 0)
    {
        fib(x);
    }


    return 0;
}
