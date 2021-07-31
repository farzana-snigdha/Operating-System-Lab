#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>


int main(int argc, char *argv[])
{
    pid_t pid1,pid2;
    //pid1=getpid();
    //pid2=getppid();
    pid1=fork();
    if(pid1<0)
        printf("Forking Failed\n");
    else if(pid1==0)
    {
        sleep(1);
        printf("Child process\n");
    }
    else if(pid1>0)
    {
        wait(NULL);
        printf("Parent process\n");
    }
    //printf("parent pid: %d\n",pid2);
    return 0;
}
