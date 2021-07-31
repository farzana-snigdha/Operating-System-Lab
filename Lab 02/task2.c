#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>

int main()
{

    int x = 0;
    pid_t pid1;
    pid1 = fork();


    if(pid1<0)
    {
        printf("failed\n");
    }
    else if (pid>0)
    {
        wait(NULL);
        x += 119;
        printf("%d\n", x);
    }
    else if(pid1 == 0)
    {

        x += 180042119;
        printf("child process: %d\n", x);
    }



    return 0;
}
